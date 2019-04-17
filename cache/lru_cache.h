//
// Created by Shuangquan Li on 30/09/2018.
//

#ifndef __CACHE_LRU_CACHE_H__
#define __CACHE_LRU_CACHE_H__

#include <functional>
#include <list>
#include <iostream>
#include <memory>
#include <unordered_map>

namespace cil {


template<
        typename Key,
        typename Value,
        typename Hash = std::hash<Key>,
        typename Pred = std::equal_to<Key>
>
class lru_cache {
public:
    typedef Key                                   key_type;
    typedef Value                                 value_type;
    typedef std::pair<const key_type, value_type> kv_pair;

private:
    typedef std::list<kv_pair>                                        __list_type;
    typedef typename __list_type::iterator                            __list_iterator;
    typedef typename __list_type::const_iterator                      __list_const_iterator;
    typedef std::unordered_map<key_type, __list_iterator, Hash, Pred> __map_type;
    typedef typename __map_type::iterator                             __map_iterator;
    typedef typename __map_type::const_iterator                       __map_const_iterator;

public:
    typedef __list_iterator       iterator;
    typedef __list_const_iterator const_iterator;

public:
    lru_cache(size_t capacity): __capacity(capacity) {}

    size_t size() const {
        return __kv_list.size();
    }

    size_t capacity() const {
        return __capacity;
    }

    bool empty() const {
        return size() == 0;
    }

    void clear() {
        __kv_list.clear();
        __key_to_list_it.clear();
    }

    void set(const key_type& key, const value_type& value) {
        __map_iterator map_it = __key_to_list_it.find(key);
        if (map_it != __key_to_list_it.end()) {
            map_it->second->second = value;
            __move_to_first(map_it->second);
            return;
        }
        __kv_list.push_front(std::make_pair(key, value));
        __key_to_list_it[key] = __kv_list.begin();
        if (size() > capacity()) {
            __remove_last();
        }
    }

    bool get(const key_type& key, value_type& value) {
        return __get<true>(key, value);
    }

    bool peek(const key_type& key, value_type& value) {
        return __get<false>(key, value);
    }

    void remove(const key_type& key) {
        __map_iterator map_it = __key_to_list_it.find(key);
        if (map_it == __key_to_list_it.end()) {
            return;
        }
        __kv_list.erase(map_it->second);
        __key_to_list_it.erase(map_it);
    }

    bool contains(const key_type& key) const {
        return __key_to_list_it.count(key) > 0;
    }

    iterator begin() {
        return __kv_list.begin();
    }

    iterator end() {
        return __kv_list.end();
    }

    const_iterator cbegin() const {
        return __kv_list.cbegin();
    }

    const_iterator cend() const {
        return __kv_list.cend();
    }

private:
    template <bool move_to_first>
    bool __get(const key_type& key, value_type& value) {
        __map_iterator map_it = __key_to_list_it.find(key);
        if (map_it == __key_to_list_it.end()) {
            return false;
        }
        value = map_it->second->second;
        if (move_to_first) {
            __move_to_first(map_it->second);
        }
        return true;
    }

    void __move_to_first(__list_iterator it) {
        __kv_list.splice(__kv_list.begin(), __kv_list, it);
    }

    void __remove_last() {
        remove(__kv_list.back().first);
    }

private:
    __list_type __kv_list;
    __map_type  __key_to_list_it;
    size_t      __capacity;
};

template<
        typename Key,
        typename Value,
        typename Hash = std::hash<Key>,
        typename Pred = std::equal_to<Key>
>
std::ostream& operator<<(std::ostream& os, const lru_cache<Key, Value, Hash, Pred>& lru) {
    os << "[";
    for (typename lru_cache<Key, Value, Hash, Pred>::const_iterator it = lru.cbegin(), e = lru.cend(); it != e; ++it) {
        if (it != lru.cbegin()) os << ", ";
        os << "(" << it->first << ", " << it->second << ")";
    }
    os << "]" << std::flush;
    return os;
};


} // namespace cil

#endif //__CACHE_LRU_CACHE_H__
