/*
 * segment-tree header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2023-2-24
 */

#ifndef __SEGMENT_TREE_H__
#define __SEGMENT_TREE_H__

#include <cassert>
#include <vector>
#include <functional>


// Segment tree with complete binary tree. tree_[1] is root.
// Left child of index i is i*2, right child is i*2+1.
// Leaf nodes are tree_[n_: n_*2], equal to array[0:n_] where n_ is array's 
// size. And these leaf nodes are not necessarily on same level.
template<typename T = int, typename Fun = std::plus<T>>
class segment_tree {
    int n_;  // origin array's size, half of tree_'s size
    std::vector<T> tree_; // tree nodes
    const Fun fun_{};

public:
    segment_tree(int n, const T& initial = T{}) : n_(n), tree_(n << 1, initial) {}

    segment_tree(const std::vector<T>& a) {
        n_ = a.size();
        tree_.resize(n_ << 1);
        for (int i = 0; i < n_; ++i) tree_[n_ + i] = a[i];
    }

    // query of range [l, r)
    T query(int l, int r, const T& initial = T{}) const {
        assert(l >= 0 && l < n_);
        assert(r >= 0 && r < n_);
        T ret = initial;
        l += n_;
        r += n_;
        while (l < r) {
            if (l & 1) ret = fun_(ret, tree_[l++]);
            if (r & 1) ret = fun_(ret, tree_[--r]);
            l >>= 1;
            r >>= 1;
        }
        return ret;
    }

    // get value of a[idx]
    const T& get(int idx) const { assert(idx >= 0 && idx < n_); return tree_[n_ + idx]; }

    // set a[idx] = v, then update tree.
    void set(int idx, const T& v) {
        assert(idx >= 0 && idx < n_);
        idx += n_;
        tree_[idx] = v;
        idx >>= 1;
        while (idx > 0) {
            tree_[idx] = fun_(tree_[idx << 1], tree_[idx << 1 | 1]);
            idx >>= 1;
        }
    }

    // set a[idx] = fun_(a[idx], v), then update tree.
    void update(int idx, const T& v) {
        assert(idx >= 0 && idx < n_);
        idx += n_;
        tree_[idx] = fun_(tree_[idx], v);
        idx >>= 1;
        while (idx > 0) {
            tree_[idx] = fun_(tree_[idx << 1], tree_[idx << 1 | 1]);
            idx >>= 1;
        }
    }
};


template<typename T = int, typename Fun = std::plus<T>>
class recursive_segment_tree {
    int n_ = 0;  // origin array's size
    std::vector<T> tree_; // tree_[1] is root
    std::vector<int> array_idx_to_tree_idx_; // leaf nodes
    const Fun fun_{};

    // node idx, range [l, r)
    void build(int idx, int l, int r, const std::vector<T>& a) {
        assert(l < r);
        if (idx >= tree_.size()) tree_.resize(idx);
        if (l == r - 1) {
            tree_[idx] = a[l];
            array_idx_to_tree_idx_[l] = idx;
            return;
        }
        int m = (l + r) >> 1;
        build(idx << 1, l, m, a);
        build(idx << 1 | 1, m, r, a);
        tree_[idx] = fun_(tree_[idx << 1], tree_[idx << 1 | 1]);
    }

    // query range [a, b)
    T query(int idx, int l, int r, int a, int b, const T& initial = T{}) const {
        if (l >= b || r <= a) return initial;
        if (l >= a && r <= b) return tree_[idx];
        int m = (l + r) >> 1;
        auto x = query(idx << 1, l, m, a, b, initial);
        auto y = query(idx << 1 | 1, m, r, a, b, initial);
        return fun_(x, y);
    }
public:

    recursive_segment_tree(int n, const T& initial = T{}) { init(vector<T>(n, initial));}

    recursive_segment_tree(const std::vector<T>& a) { init(a); }

    void init(const std::vector<T>& a) {
        assert(!a.empty());
        n_ = a.size();
        array_idx_to_tree_idx_.resize(n_);
        tree_.reserve(n_ << 2);
        build(1, 0, n_, a);
    }

    // query of range [a, b)
    T query(int a, int b) const {
        assert(a >= 0 && a < n_);
        assert(b >= 0 && b < n_);
        return query(1, 0, n_, a, b);
    }

    // get value of a[idx]
    const T& get(int idx) const {
        assert(idx >= 0 && idx < n_);
        return tree_[array_idx_to_tree_idx_[idx]];
    }

    // set a[idx] = v, then update tree.
    void set(int idx, const T& v) {
        assert(idx >= 0 && idx < n_);
        idx = array_idx_to_tree_idx_[idx];
        tree_[idx] = v;
        idx >>= 1;
        while (idx > 0) {
            tree_[idx] = fun_(tree_[idx << 1], tree_[idx << 1 | 1]);
            idx >>= 1;
        }
    }

    // set a[idx] = fun_(a[idx], v), then update tree.
    void update(int idx, const T& v) {
        assert(idx >= 0 && idx < n_);
        idx = array_idx_to_tree_idx_[idx];
        tree_[idx] = fun_(tree_[idx], v);
        idx >>= 1;
        while (idx > 0) {
            tree_[idx] = fun_(tree_[idx << 1], tree_[idx << 1 | 1]);
            idx >>= 1;
        }
    }
};

#endif
