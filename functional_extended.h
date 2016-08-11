/*
 * functional-extended header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-8-6
 * last edit on 2016-8-11, add maxone, minone
 */

#ifndef __FUNCTIONAL_EXTENDED_H__
#define __FUNCTIONAL_EXTENDED_H__

#include <vector>
#include <functional>

template<typename T, typename Compare = std::less<T>>
struct maxone : std::binary_function<T, T, T> {
	T operator() (const T& a, const T& b) {
		return Compare()(a, b) ? b : a;
	}
};

template<typename T, typename Compare = std::less<T>>
struct minone : std::binary_function<T, T, T> {
	T operator() (const T& a, const T& b) {
		return Compare()(a, b) ? a : b;
	}
};

template<typename T, T mod>
struct plus_modulus : std::binary_function<T, T, T> {
	T operator () (const T& a, const T& b) const {
		T ret = (a + b) % mod;
		if (ret < 0) ret += mod;
		return ret;
	}
};

template<typename T, T mod>
struct minus_modulus : std::binary_function<T, T, T> {
	T operator () (const T& a, const T& b) {
		T ret = (a - b) % mod;
		if (ret < 0) ret += mod;
		return ret;
	}
};

template<typename T, T mod>
struct multiplies_modulus : std::binary_function<T, T, T> {
	T operator () (const T& a, const T& b) {
		return a * b % mod;
	}
};

/* eof */
#endif
