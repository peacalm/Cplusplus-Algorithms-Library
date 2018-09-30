/**
 * delist header
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2018.8.22
 */

#ifndef __DELIST_H__
#define __DELIST_H__

#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <utility>


template <typename T>
class __delist_node {
public:
    typedef T value_type;
    typedef std::shared_ptr<__delist_node> node_ptr;

    value_type __val;
    node_ptr __link1, __link2;
public:

    /// Self loop as default. Which one is link1 and which one is link2 could be arbitrary.
    __delist_node(const value_type& val = value_type(),
                  const node_ptr& link1 = nullptr, const node_ptr& link2 = nullptr):
            __val(val), __link1(link1), __link2(link2) {}

    ~__delist_node() {}

    node_ptr& link_not_to(const node_ptr& p) {
        return __link1 == p ? __link2 : __link1;
    }

    node_ptr& link_to(const node_ptr& p) {
        return __link1 == p ? __link1 : __link2;
    }

    void clear_links() {
        __link1 = __link2 = nullptr;
    }

    void both_link_to(const node_ptr& p) {
        __link1 = __link2 = p;
    }
};


template <typename T>
class __delist_const_iterator {
    typedef __delist_node<T>                node_type;
    typedef typename node_type::node_ptr    node_ptr;
public:
    typedef T                               value_type;
    typedef T&                              reference;
    typedef const T&                        const_reference;
    typedef T*                              pointer;
    typedef const T*                        const_pointer;
    typedef std::bidirectional_iterator_tag iterator_category;
protected:
    node_ptr __cur;
    node_ptr __next;
public:

    __delist_const_iterator(const node_ptr& cur = nullptr, const node_ptr& next = nullptr): __cur(cur), __next(next) {}

    __delist_const_iterator(const __delist_const_iterator& rhs): __cur(rhs.__cur), __next(rhs.__next) {}

    __delist_const_iterator& operator ++ () {
        node_ptr nn = __next->link_not_to(__cur);
        __cur = __next;
        __next = nn;
        return *this;
    }

    __delist_const_iterator operator ++ (int) {
        node_ptr ret(*this);
        node_ptr nn = __next->link_not_to(__cur);
        __cur = __next;
        __next = nn;
        return ret;
    }

    __delist_const_iterator& operator -- () {
        node_ptr pre = __cur->link_not_to(__next);
        __next = __cur;
        __cur = pre;
        return *this;
    }

    __delist_const_iterator operator -- (int) {
        node_ptr ret(*this);
        node_ptr pre = __cur->link_not_to(__next);
        __next = __cur;
        __cur = pre;
        return ret;
    }

    const_reference operator * () const {
        return __cur->__val;
    }

    const_pointer operator -> () const {
        return &(__cur->__val);
    }

    bool operator == (const __delist_const_iterator& rhs) const {
        return __cur == rhs.__cur;
    }

    bool operator != (const __delist_const_iterator& rhs) const {
        return __cur != rhs.__cur;
    }

    __delist_const_iterator& operator = (const __delist_const_iterator& rhs) {
        __cur = rhs.__cur;
        __next = rhs.__next;
        return *this;
    }
};


template <typename T>
class __delist_iterator: public __delist_const_iterator<T> {
    typedef __delist_const_iterator<T>      base_type;
    typedef __delist_node<T>                node_type;
    typedef typename node_type::node_ptr    node_ptr;
public:
    typedef T                               value_type;
    typedef T&                              reference;
    typedef const T&                        const_reference;
    typedef T*                              pointer;
    typedef const T*                        const_pointer;
    typedef std::bidirectional_iterator_tag iterator_category;
public:

    __delist_iterator(const node_ptr& cur = nullptr, const node_ptr& next = nullptr): base_type(cur, next) {}

    __delist_iterator(const __delist_iterator& rhs): base_type(rhs.__cur, rhs.__next) {}

    reference operator * () {
        return base_type::__cur->__val;
    }

    pointer operator -> () {
        return &(base_type::__cur->__val);
    }
};


template <typename T>
class delist {
    typedef __delist_node<T>                    node_type;
    typedef typename node_type::node_ptr        node_ptr;
public:
    typedef T                                   value_type;
    typedef T&                                  reference;
    typedef const T&                            const_reference;
    typedef T*                                  pointer;
    typedef const T*                            const_pointer;
    typedef __delist_iterator<value_type>       iterator;
    typedef __delist_const_iterator<value_type> const_iterator;
    typedef size_t                              size_type;

private:
    node_ptr __phead; /// link1 point to next(the first one), link2 previous(last one).
    size_type __size;

private:

    node_ptr make_new_node(const value_type& v = value_type(),
                           const node_ptr& l1 = nullptr, const node_ptr& l2 = nullptr) {
        return std::make_shared<node_type>(v, l1, l2);
    }

public:

    delist(): __phead(make_new_node()), __size(0) {
        __phead->both_link_to(__phead);
    }

    delist(std::initializer_list<value_type> init): __phead(make_new_node()), __size(0) {
        __phead->both_link_to(__phead);
        for (const value_type& i : init) {
            push_back(i);
        }
    }

    ~delist() {
        clear();
        __phead->clear_links();
        __phead = nullptr;
    }

    void clear() {
        node_ptr pre = __phead;
        node_ptr it = __phead->__link1;
        while (it != __phead) {
            node_ptr nxt = it->link_not_to(pre);
            it->clear_links();
            pre = it;
            it = nxt;
        }
        __phead->both_link_to(__phead);  // keep __phead self loop when clear
        __size = 0;
    }

    delist& reverse() {
        std::swap(__phead->__link1, __phead->__link2);
        return *this;
    }

    size_type size() const { return __size; }

    bool empty() const { return __size == 0; }

    iterator end() {
        return iterator(__phead, __phead->__link1);
    }

    iterator begin() {
        node_ptr first = __phead->__link1;
        node_ptr second = first->link_not_to(__phead);
        return iterator(first, second);
    }

    const_iterator cend() const {
        return const_iterator(__phead, __phead->__link1);
    }

    const_iterator cbegin() const {
        node_ptr first = __phead->__link1;
        node_ptr second = first->link_not_to(__phead);
        return const_iterator(first, second);
    }

    void push_back(const value_type& v) {
        node_ptr last = __phead->__link2;
        node_ptr new_node = make_new_node(v, __phead, last);

        last->link_to(__phead) = new_node;
        __phead->__link2 = new_node;
        ++__size;
    }

    void push_front(const value_type& v) {
        reverse();
        push_back(v);
        reverse();
    }

    reference front() {
        return __phead->__link1->__val;
    }

    const_reference front() const {
        return __phead->__link1->__val;
    }

    reference back() {
        return __phead->__link2->__val;
    }

    const_reference back() const {
        return __phead->__link2->__val;
    }

    value_type pop_back() {
        if (__size <= 0) {
            throw std::runtime_error("delist is empty");
        }
        node_ptr last = __phead->__link2;
        value_type ret = last->__val;
        node_ptr new_last = last->link_not_to(__phead);
        new_last->link_to(last) = __phead;
        __phead->__link2 = new_last;
        --__size;
        return ret;
    }

    value_type pop_front() {
        reverse();
        value_type ret = pop_back();
        reverse();
        return ret;
    }

    /// Extend rhs into this on the end, then empty rhs. No node copied, but all transferred, preform in O(1) time.
    delist& extend(delist& rhs) {
        if (!rhs.__size) return *this;
        if (*this == rhs) return *this;

        node_ptr last = __phead->__link2;
        node_ptr rhs_first = rhs.__phead->__link1;
        last->link_to(__phead) = rhs_first;
        rhs_first->link_to(rhs.__phead) = last;

        node_ptr rhs_last = rhs.__phead->__link2;
        rhs_last->link_to(rhs.__phead) = __phead;
        __phead->__link2 = rhs_last;

        rhs.__phead->both_link_to(rhs.__phead);

        __size += rhs.__size;
        rhs.__size = 0;

        return *this;
    }

    bool operator == (const delist& rhs) const {
        return __phead == rhs.__phead;
    }

    bool operator != (const delist& rhs) const {
        return !operator==(rhs);
    }
};


template <typename T>
std::ostream& operator << (std::ostream& os, const delist<T>& dl) {
    os << "[";
    for (typename delist<T>::const_iterator it = dl.cbegin(), e = dl.cend(); it != e; ++it) {
        if (it == dl.cbegin()) {
            os << *it;
            continue;
        }
        os << ", " << *it;
    }
    os << "]" << std::flush;
    return os;
}

/* eof */
#endif