//
// Created by Shuangquan Li on 30/09/2018.
//

#ifndef __CACHE_EXPIRING_LRU_CACHE_H__
#define __CACHE_EXPIRING_LRU_CACHE_H__

#include <ctime>
#include "lru_cache.h"

namespace cil {

namespace {

struct unix_time_getter {
    time_t operator()() const {
        return time(nullptr);
    }
};

} // anonymous namespace

template<
        typename Key,
        typename Value,
        typename Time = time_t,
        typename TimeGetter = unix_time_getter,
        typename Hash = std::hash<Key>,
        typename Pred = std::equal_to<Key>
>
class expiring_lru_cache: public lru_cache<Key, std::pair<Value, Time>, Hash, Pred> {
public:
    typedef Key key_type;
    typedef Value value_type;
    typedef Time time_type;
    typedef std::pair<value_type, time_type> value_time_pair;

private:
    typedef lru_cache<Key, value_time_pair, Hash, Pred> __base;
    time_type __time_out;

public:
    expiring_lru_cache(size_t capacity, time_type time_out): __base(capacity), __time_out(time_out) {}

    bool get(const key_type& key, value_type& value) {
        value_time_pair vt;
        bool success = __base::get(key, vt);
        if (!success) {
            return false;
        }
        if (__is_time_out(vt.second)) {
            __base::remove(key);
            return false;
        }
        value = vt.first;
        return true;
    }

    void set(const key_type& key, const value_type& value) {
        __base::set(key, std::make_pair(value, __get_current_time() + __time_out));
    }

    void set(const key_type& key, const value_type& value, time_type time_out) {
        __base::set(key, std::make_pair(value, __get_current_time() + time_out));
    }

    void clear_time_out() {
        for (auto it = __base::begin(), e = __base::end(); it != e;) {
            if (!__is_time_out(it->second.second)) {
                ++it;
                continue;
            }
            auto key = it->first;
            ++it;
            __base::remove(key);
        }
    }

private:
    bool __is_time_out(time_type t) {
        return t < __get_current_time();
    }

    time_type __get_current_time() const {
        return TimeGetter()();
    }
};


template<
        typename Key,
        typename Value,
        typename Time = time_t,
        typename TimeGetter = unix_time_getter,
        typename Hash = std::hash<Key>,
        typename Pred = std::equal_to<Key>
>
std::ostream& operator<<(std::ostream& os, const expiring_lru_cache<Key, Value, Time, TimeGetter, Hash, Pred>& lru) {
    os << "[";
    for (typename expiring_lru_cache<Key, Value, Time, TimeGetter, Hash, Pred>::const_iterator it = lru.cbegin(),
                 e = lru.cend(); it != e; ++it) {
        if (it != lru.cbegin()) os << ", ";
        os << "(" << it->first << ", " << it->second.first << ", " << it->second.second << ")";
    }
    os << "]" << std::flush;
    return os;
};

} // namespace cil

#endif // __CACHE_EXPIRING_LRU_CACHE_H__
