//
// Created by Shuangquan Li on 09/11/2018.
//

#ifndef __CACHE_EXPIRING_LRU_CACHED_ADAPTER_H__
#define __CACHE_EXPIRING_LRU_CACHED_ADAPTER_H__


#include <algorithm>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "expiring_lru_cache.h"
#include "lru_cache.h"

namespace cil {

/// Getter is the origin data-fetcher type with key-value queries. Key and Value are key type and value type of Getter.
/// Key must be comparable by operator "<" and "==". Getter must have thread-safe, no-exception-throwing "get" and
/// "mget" method:
///     bool get(const Key&, Value&) noexcept;
///     bool mget(const std::vector<Key>&, std::vector<Value>&) noexcept;
/// Then, using expiring_lru_cached_adapter<Key, Value, Getter, Time, TimeGetter, Hash, Pred> instead of Getter to obtain
/// expiring lru cached new getter-type.
/// cache_size is the total cache size, time_out is time duration to expire, cache_num is inner divided cache num which
/// should range by concurrency.
template <
        typename Key,
        typename Value,
        typename Getter,
        typename Time = time_t,
        typename TimeGetter = unix_time_getter,
        typename Hash = std::hash<Key>,
        typename Pred = std::equal_to<Key>
>
class expiring_lru_cached_adapter {
    
public:
    typedef Key        key_type;
    typedef Value      value_type;
    typedef Getter     getter_type;
    typedef Time       time_type;
    typedef TimeGetter time_getter;
    typedef Hash       hash_type;
    typedef Pred       pred_type;

public:
    template<typename ...Args>
    expiring_lru_cached_adapter(size_t cache_size, time_type time_out, size_t cache_num, Args&... args):
            __cache_num(cache_num),
            __caches(__cache_num, expiring_lru_cache<key_type, value_type>(cache_size / cache_num, time_out)),
            __mtxes(__cache_num),
            __cond_vars(__cache_num),
            __loading_keys(__cache_num),
            __getter(args...) {}

    bool get(const key_type& key, value_type& value) {
        size_t cache_id = __get_cache_id(key);
        bool got_cached_value = __query_cache(key, value, cache_id);
        if (got_cached_value) {
            return true;
        }
        bool got_origin_value = false;
        try {
            got_origin_value = __getter.get(key, value);
        }
        catch (...) {
            got_origin_value = false;
        }
        std::unique_lock<std::mutex> lk(__mtxes[cache_id]);
        if (got_origin_value) {
            __caches[cache_id].set(key, value);
        }
        __notify(key, cache_id);
        return got_origin_value;
    }

    bool mget(const std::vector<key_type>& keys, std::vector<value_type>& values) {
        values.resize(keys.size());
        std::vector<size_t> cache_ids;
        for (auto& k: keys) {
            cache_ids.push_back(__get_cache_id(k));
        }
        std::vector<std::pair<key_type*, size_t>> keyptr_pos_paires;
        for (size_t i = 0; i < keys.size(); ++i) {
            keyptr_pos_paires.emplace_back(&keys[i], i);
        }
        std::sort(keyptr_pos_paires.begin(), keyptr_pos_paires.end(),
                  [&](const std::pair<key_type*, size_t >& lhs, const std::pair<key_type*, size_t >& rhs) {
                      return *(lhs.first) < *(rhs.first);
                  }
        );
        std::vector<key_type> missed_keys;
        std::vector<size_t> missed_poses;
        std::vector<value_type> missed_values;
        std::vector<size_t> dup_query_kpp_idx;
        for (size_t i = 0; i < keyptr_pos_paires.size(); ++i) {
            std::pair<key_type*, size_t>& p = keyptr_pos_paires[i];
            key_type& key = *(p.first);
            size_t pos = p.second;
            if (i > 0 && key == *(keyptr_pos_paires[i - 1].first)) {
                dup_query_kpp_idx.push_back(i);
                continue;
            }
            bool got_cached_result = __query_cache(key, values[pos], cache_ids[pos]);
            if (!got_cached_result) {
                missed_keys.push_back(key);
                missed_poses.push_back(pos);
            }
        }
        auto process_dup_queries = [&]() {
            for (size_t idx: dup_query_kpp_idx) {
                size_t query_pos = keyptr_pos_paires[idx].second;
                size_t value_pos = keyptr_pos_paires[idx - 1].second;
                values[query_pos] = values[value_pos];
            }
        };
        if (missed_keys.empty()) {
            process_dup_queries();
            return true;
        }
        bool got_origin_value = false;
        try {
            got_origin_value = __getter.mget(missed_keys, missed_values);
        }
        catch (...) {
            got_origin_value = false;
        }
        for (size_t i = 0; i < missed_keys.size(); ++i) {
            size_t pos = missed_poses[i];
            size_t cache_id = cache_ids[pos];
            std::unique_lock<std::mutex> lk(__mtxes[cache_id]);
            if (got_origin_value) {
                values[pos] = missed_values[i];
                __caches[cache_id].set(missed_keys[i], missed_values[i]);
            }
            __notify(missed_keys[i], cache_id);
        }
        process_dup_queries();
        return got_origin_value;
    }

    getter_type& getter() {
        return __getter;
    }

private:
    size_t __get_cache_id(const key_type& key) const {
        return (size_t)(std::hash<key_type>{}(key)) % (size_t)(__cache_num);
    }

    bool __wait(std::unique_lock<std::mutex>& lk, const key_type& key, size_t cache_id) {
        if (!__loading_keys[cache_id].count(key)) {
            return false;
        }
        __cond_vars[cache_id].wait(lk, [&] {
            return !__loading_keys[cache_id].count(key);
        });
        return true;
    }

    void __notify(const key_type& key, size_t cache_id) {
        __loading_keys[cache_id].erase(key);
        __cond_vars[cache_id].notify_all();
    }

    bool __query_cache(const key_type& key, value_type& value, size_t cache_id) {
        std::unique_lock<std::mutex> lk(__mtxes[cache_id]);
        bool already_loaded = __wait(lk, key, cache_id);
        bool got_cached_value = __caches[cache_id].get(key, value);
        if (got_cached_value) {
            return true;
        }
        __loading_keys[cache_id].insert(key);
        return false;
    }

private:
    size_t                                                                                              __cache_num;
    std::vector<expiring_lru_cache<key_type, value_type, time_type, time_getter, hash_type, pred_type>> __caches;
    std::vector<std::mutex>                                                                             __mtxes;
    std::vector<std::condition_variable>                                                                __cond_vars;
    std::vector<std::unordered_set<key_type>>                                                           __loading_keys;
    getter_type                                                                                         __getter;
};

} // namespace cil


#endif
