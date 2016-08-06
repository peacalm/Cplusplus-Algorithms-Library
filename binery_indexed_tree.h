/*
 * binery-indexed-tree header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2015-12-31
 * latest edit on 2016-5-13 add two dimension's BIT2, BIT02
 * latest edit on 2016-7-3 add modulo operations, madd, msum
 * latest edit on 2016-8-6 add two new implements binary_indexed_tree ans binary_indexed_tree_2d.
 */

#ifndef __BINERY_INDEXED_TREE_H__
#define __BINERY_INDEXED_TREE_H__

#include <cassert>
#include <cstring>
#include <vector>
#include <functional>


template<typename T, typename Operator = std::plus<T>>
class binary_indexed_tree {
	std::vector<T> __c;
	Operator __op;
	int __n;
public:
	binary_indexed_tree() : __n(0) {}
	binary_indexed_tree(int n, T v = 0) { __c.resize(n, v); __n = n; }
	void clear() { __c.clear(); __n = 0; }
	void fill(T v) { for (int i = 0; i < __n; ++i) __c[i] = v; }
	void resize(int n, T v = 0) { __c.clear(); __c.resize(n, v); __n = n; }
	int size() { return __n; }
	void add(int x, T d) {
		for (int i = x; i < __n; i |= i + 1)
			__c[i] = __op(__c[i], d);
	}
	T accu(int x) {
		T ret;
		if (__op(1, 0) == 1) ret = 0;
		else if (__op(1, 1) == 1) ret = 1;
		else if (__op(1, T(-1)) == 1) ret = T(-1);
		else assert(0);
		for (int i = x; i >= 0; i = (i & i + 1) - 1)
			ret = __op(ret, __c[i]);
		return ret;
	}
	T accu(int l, int r) { return accu(r) - accu(l - 1); }
};


template<typename T, typename Operator = std::plus<T>>
class binary_indexed_tree_2d {
	std::vector<std::vector<T>> __c;
	Operator __op;
	int __n, __m;
public:
	binary_indexed_tree_2d() : __n(0), __m(0) {}
	binary_indexed_tree_2d(int n, int m, T v = 0) {
		__c.resize(n, std::vector<T>(m, v));
		__n = n; __m = m;
	}
	void clear() { __c.clear(); __n = __m = 0; }
	void fill(T v) {
		for (int i = 0; i < __n; ++i)
			for (int j = 0; j < __m; ++j)
				__c[i][j] = v;
	}
	void resize(int n, int m, T v = 0) {
		__c.clear();
		__c.resize(n, std::vector<T>(m, v));
		__n = n; __m = m;
	}
	std::pair<int, int> size() { return make_pair(__n, __m); }
	void add(int x, int y, T d) {
		for (int i = x; i < __n; i |= i + 1)
			for (int j = y; j < __m; j |= j + 1)
				__c[i][j] = __op(__c[i], d);
	}
	T accu(int i) {
		T ret;
		if (__op(1, 0) == 1) ret = 0;
		else if (__op(1, 1) == 1) ret = 1;
		else if (__op(1, T(-1)) == 1) ret = T(-1);
		else assert(0);
		for (; i >= 0; i = (i & i + 1) - 1)
			ret = __op(ret, __c[i]);
		return ret;
	}
	T accu(int l, int r) { return accu(r) - accu(l - 1); }
};





// 1 << 20 == 1048576 ~== 1e6

template<int n = 1048576, typename T = int> class BIT {
	T c[n];
public: 
	BIT() { memset(c, 0, sizeof(c)); }
	void clear() { memset(c, 0, sizeof(c)); }
	int add(int i, T d) { 
		if (i <= 0) return -1; 
		for (; i < n; i += i & -i) c[i] += d; 
		return 0; 
	} 
	T sum(int i) { 
		T sum = 0; 
		for (; i > 0; i -= i & -i) sum += c[i]; 
		return sum; 
	} 
	T sum(int l, int r) { return sum(r) - sum(l - 1); }

	template<typename U>
	int madd(int i, T d, U mod) {
		if (i <= 0) return -1;
		for (; i < n; i += i & -i) {
			c[i] = (c[i] + d) % mod;
			if (c[i] < 0) c[i] += mod;
		}
		return 0;
	}
	template<typename U>
	T msum(int i, U mod) {
		T sum = 0;
		for (; i > 0; i -= i & -i) {
			sum = (sum + c[i]) % mod;
			if (sum < 0) sum += mod;
		}
		return sum;
	}
	template<typename U>
	T msum(int l, int r, U mod) {
		T ret = (msum(r) - msum(l - 1)) % mod;
		if (ret < 0) ret += mod;
		return ret;
	}
};



template<int n = 1048576, typename T = int> class BIT0 {
	T c[n];
public: 
	BIT0() { memset(c, 0, sizeof(c)); }
	void clear() { memset(c, 0, sizeof(c)); }
	int add(int i, T d) {
		if (i < 0) return -1;
		for (; i < n; i = i | (i + 1)) c[i] += d; 
		return 0;
	} 
	T sum(int i) { 
		T sum = 0;
		for (; i >= 0; i = (i & (i + 1)) - 1) sum += c[i]; 
		return sum;
	} 
	T sum(int l, int r) { return sum(r) - sum(l - 1); }

	template<typename U>
	int madd(int i, T d, U mod) {
		if (i < 0) return -1;
		for (; i < n; i = i | (i + 1)) {
			c[i] = (c[i] + d) % mod;
			if (c[i] < 0) c[i] += mod;
		}
		return 0;
	}
	template<typename U>
	T msum(int i, U mod) {
		T sum = 0;
		for (; i >= 0; i = (i & (i + 1)) - 1) {
			sum = (sum + c[i]) % mod;
			if (sum < 0) sum += mod;
		}
		return sum;
	}
	template<typename U>
	T msum(int l, int r, U mod) {
		T ret = (msum(r) - msum(l - 1)) % mod;
		if (ret < 0) ret += mod;
		return ret;
	}
};






// two dimension

template<int n = 1024, int m = n, typename T = int> class BIT2 {
	T c[n][m];
public:
	BIT2() { memset(c, 0, sizeof(c)); }
	void clear() { memset(c, 0, sizeof(c)); }
	int add(int x, int y, T d) {
		if (x <= 0 || y <= 0) return -1;
		for (int i = x; i < n; i += i & -i)
			for (int j = y; j < m; j += j & -j)
				c[i][j] += d;
		return 0;
	}
	T sum(int x, int y) {
		T sum = 0;
		for (int i = x; i > 0; i -= i & -i)
			for (int j = y; j > 0; j -= j & -j)
				sum += c[i][j];
		return sum;
	}
	T sum(int r1, int c1, int r2, int c2) {
		return sum(r2, c2) + sum(r1 - 1, c1 - 1) - sum(r2, c1 - 1) - sum(r1 - 1, c2);
	}

	template<typename U>
	int madd(int x, int y, T d, U mod) {
		if (x <= 0 || y <= 0) return -1;
		for (int i = x; i < n; i += i & -i)
			for (int j = y; j < m; j += j & -j) {
				c[i][j] = (c[i][j] + d) % mod;
				if (c[i][j] < 0) c[i][j] += mod;
			}
		return 0;
	}
	template<typename U>
	T msum(int x, int y, U mod) {
		T sum = 0;
		for (int i = x; i > 0; i -= i & -i)
			for (int j = y; j > 0; j -= j & -j) {
				sum = (sum + c[i]) % mod;
				if (sum < 0) sum += mod;
			}
		return sum;
	}
	template<typename U>
	T msum(int r1, int c1, int r2, int c2, U mod) {
		T ret = (msum(r2, c2, mod) + msum(r1 - 1, c1 - 1, mod) - msum(r2, c1 - 1, mod) - msum(r1 - 1, c2, mod)) % mod;
		if (ret < 0) ret += mod;
		return ret;
	}
};


template<int n = 1024, int m = n, typename T = int> class BIT02 {
	T c[n][m];
public:
	BIT02() { memset(c, 0, sizeof(c)); }
	void clear() { memset(c, 0, sizeof(c)); }
	int add(int x, int y, T d) {
		if (x <= -1 || y <= -1) return -1;
		for (int i = x; i < n; i |= i + 1)
			for (int j = y; j < m; j |= j + 1)
				c[i][j] += d;
		return 0;
	}
	T sum(int x, int y) {
		T sum = 0;
		for (int i = x; i >= 0; i = (i & i + 1) - 1)
			for (int j = y; j >= 0; j = (j & j + 1) - 1)
				sum += c[i][j];
		return sum;
	}
	T sum(int r1, int c1, int r2, int c2) {
		return sum(r2, c2) + sum(r1 - 1, c1 - 1) - sum(r2, c1 - 1) - sum(r1 - 1, c2);
	}

	template<typename U>
	int madd(int x, int y, T d, U mod) {
		if (x <= -1 || y <= -1) return -1;
		for (int i = x; i < n; i |= i + 1)
			for (int j = y; j < m; j |= j + 1) {
				c[i][j] = (c[i][j] + d) % mod;
				if (c[i][j] < 0) c[i][j] += mod;
			}
		return 0;
	}
	template<typename U>
	T msum(int x, int y, U mod) {
		T sum = 0;
		for (int i = x; i >= 0; i = (i & i + 1) - 1)
			for (int j = y; j >= 0; j = (j & j + 1) - 1) {
				sum = (sum + c[i]) % mod;
				if (sum < 0) sum += mod;
			}
		return sum;
	}
	template<typename U>
	T msum(int r1, int c1, int r2, int c2, U mod) {
		T ret = (msum(r2, c2, mod) + msum(r1 - 1, c1 - 1, mod) - msum(r2, c1 - 1, mod) - msum(r1 - 1, c2, mod)) % mod;
		if (ret < 0) ret += mod;
		return ret;
	}
};


/* eof */
#endif
