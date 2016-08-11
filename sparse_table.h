/*
 * sparse-table header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-8-11
 */

#ifndef __SPARSE_TABLE__
#define __SPARSE_TABLE__

#include <iostream>
#include <vector>

template<typename T, typename Operator>
class sparse_table {
	std::vector<std::vector<T>> __st;
	Operator __op;
public:
	sparse_table() {}
	template<typename ForwardIterator>
	sparse_table(ForwardIterator first, ForwardIterator last) { init(first, last); }
	sparse_table(const sparse_table& rhs) { __st = rhs.__st; __op = rhs.__op; }
	template<typename ForwardIterator>
	void init(ForwardIterator first, ForwardIterator last) {
		__st.clear();
		for (ForwardIterator it = first; it != last; ++it) {
			vector<T> tmp;
			tmp.push_back(*it);
			__st.push_back(tmp);
		}
		int n = (int)(__st.size());
		for (int j = 1; (1 << j) <= n; ++j)
			for (int i = 0; i + (1 << j) <= n; ++i)
				__st[i].push_back(__op(__st[i][j - 1], __st[i + (1 << (j - 1))][j - 1]));
	}
	void add(const T& v) {
		std::vector<T> tmp;
		tmp.push_back(v);
		__st.push_back(tmp);
		int j = 1;
		int r = int(__st.size());
		while (true) {
			int i = r - (1 << j);
			if (i < 0) break;
			__st[i].push_back(__op(st[i][j - 1], __st[i + (1 << (j - 1))][j - 1]));
			++j;
		}
	}
	// query interval [l, r]
	// this is for max or min query, the two interval can be overlapped. 
	// accu get same result but this is faster;
	T rmq(int l, int r) {
		int d = r - l + 1;
		int j = 0;
		while ((1 << (j + 1)) <= d) ++j;
		return __op(__st[l][j], __st[r - (1 << j) + 1][j]);
	}
	// query interval [l, r]
	// this is for sum, product, xor sum or other queries, which the interval can not be overlapped.
	template<typename ResultType>
	ResultType accu(int l, int r, ResultType ret) {
		int d = r - l + 1;
		int j = 0;
		while (d) {
			if (d & 1) {
				ret = __op(ret, __st[l][j]);
				l += 1 << j;
			}
			d >>= 1;
			++j;
		}
		return ret;
	}
	void clear() { __st.clear(); }
	size_t size() const { return __st.size(); }
	const vector<T>& operator[](int i) const { return __st[i]; }
};

template<typename T, typename Compare>
std::ostream& operator<< (std::ostream& os, const sparse_table<T, Compare>& st) {
	for (int i = 0; i < int(st.size()); ++i) {
		os << i << ":";
		for (int j = 0; j < int(st[i].size()); ++j)
			os << " " << st[i][j];
		os << std::endl;
	}
	return os;
}


/* eof */
#endif
