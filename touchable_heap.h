/*
 * touchable-heap header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-6-14
 */

#ifndef __TOUCHABLE_HEAP_H__
#define __TOUCHABLE_HEAP_H__
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>


// this touchable-heap is familiar with the STL priority_queue class,
// but this is more useful, for you can change the value of elements or 
// even remove them while they are in heap, this is what priority_queue 
// can not, and this is just how it named touchable-heap.

// `eid` means element id, when we want to push an element into the heap,
// we give it a unique id, and they form a pair, we push the pair instead.
// so we can touch the element, if only we know its `eid`. the `eid` is
// used to recognize same elements.

template<typename T, typename Compare = std::less<T> >
class touchable_heap {
public:
	typedef T value_type;
	typedef size_t size_type;
	typedef std::pair<value_type, size_type> value_with_eid_type;
private:
	std::vector<value_with_eid_type> v;
	std::map<size_type, size_type> eid2pos;
	size_type eid_cnt;
	Compare comp;
	void percolate_up(size_type vid) {
		value_with_eid_type t = v[vid];
		for (; vid > 1 && comp(t.first, v[vid >> 1].first); vid >>= 1) {
			v[vid] = v[vid >> 1];
			eid2pos[v[vid >> 1].second] = vid;
		}
		v[vid] = t;
		eid2pos[t.second] = vid;
	}
	void percolate_down(size_type vid) {
		value_with_eid_type t = v[vid];
		for (size_type child = 0; (vid << 1) < v.size(); vid = child) {
			child = vid << 1;
			if (child != v.size() - 1 && comp(v[child + 1].first, v[child].first)) {
				++child;
			}
			if (comp(v[child].first, t.first)) {
				v[vid] = v[child];
				eid2pos[v[child].second] = vid;
			}
			else {
				break;
			}
		}
		v[vid] = t;
		eid2pos[t.second] = vid;
	}
public:
	touchable_heap() : eid_cnt(0), comp(Compare()) {
		v.push_back(std::make_pair(value_type(), 0));
	}
	touchable_heap(const std::vector<value_type>& items) {
		size_type n = items.size();
		v.resize(n + 1);
		for (size_type i = 0; i < n; ++i) {
			v[i + 1] = std::make_pair(items[i], i);
		}
		for (size_type i = n >> 1; i > 0; --i) {
			percolate_down(i);
		}
	}
	~touchable_heap() {}
	void clear() {
		v.resize(1);
		eid2pos.clear();
		eid_cnt = 0;
	}
	size_type push(const value_type& val) {
		size_type eid = eid_cnt++;
		v.push_back(std::make_pair(val, eid));
		percolate_up(v.size() - 1);
		return eid;
	}
	void push(const value_type& val, size_type eid) {
		v.push_back(std::make_pair(val, eid));
		percolate_up(v.size() - 1);
	}
	value_with_eid_type pop_with_eid() {
		value_with_eid_type ret = v[1];
		size_type eid = v[1].second;
		eid2pos.erase(eid);
		if (v.size() <= 2) {
			v.pop_back();
		}
		else {
			v[1] = v.back();
			v.pop_back();
			percolate_down(1);
		}
		return ret;
	}
	value_type pop() {
		return pop_with_eid().first;
	}
	value_type top() const {
		return v[1].first;
	}
	value_with_eid_type top_with_eid() const {
		return v[1];
	}
	void touch(size_type eid, value_type val) {
		// eid not in heap, push it in
		if (eid2pos.count(eid) == 0) {
			push(val, eid);
			return;
		}
		// modify the value of eid
		size_type pos = eid2pos[eid];
		if (comp(val, v[pos].first)) {
			v[pos].first = val;
			percolate_up(pos);
		}
		else {
			v[pos].first = val;
			percolate_down(pos);
		}
	}
	size_type size() const {
		return v.size() - 1;
	}
	bool empty() const {
		return v.size() == 1;
	}
	bool has_eid(size_type eid) const {
		return eid2pos.count(eid);
	}
	value_type eid2val(size_type eid) const {
		assert(eid2pos.count(eid));
		return v[eid2pos.find(eid)->second].first;
	}
	void erase(size_type eid) {
		if (eid2pos.count(eid) == 0) return;
		size_type pos = eid2pos[eid];
		eid2pos.erase(eid);
		if (pos == v.size() - 1) {
			v.pop_back();
			return;
		}
		v[pos] = v.back();
		v.pop_back();
		eid2pos[v[pos].second] = pos;
		if (pos > 1 && comp(v[pos].first, v[pos >> 1].first)) {
			percolate_up(pos);
		}
		else {
			percolate_down(pos);
		}
	}
	value_with_eid_type operator[] (size_type i) const {
		assert(i >= 0 && i < v.size() - 1);
		return v[i + 1];
	}
	touchable_heap& operator = (const touchable_heap& rhs) {
		v = rhs.v;
		eid2pos = rhs.eid2pos;
		eid_cnt = rhs.eid_cnt;
		return *this;
	}
};


template<typename T, typename Compare>
inline std::ostream& operator << (std::ostream& os, const touchable_heap<T, Compare>& th) {
	os << "[ ";
	for (size_t i = 0; i < th.size(); ++i)
		os << th[i].first << "(" << th[i].second << ") ";
	os << "]";
	return os;
}

/* eof */
#endif
