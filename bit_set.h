/*
 * utility header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-8-23
 */

#ifndef __BIT_SET_H__
#define __BIT_SET_H__

#include <iostream>
#include <vector>
#include <string>


class bit_set {
	typedef unsigned char uchar;
	std::vector<uchar> __bits;
	size_t __size_to_vector_size(size_t n) { return (n + 7) >> 3; }
	size_t __size;
public:
	bit_set() {}
	bit_set(size_t n) : __size(n), __bits(__size_to_vector_size(n), 0) {}
	bit_set(const bit_set& b) : __size(b.__size), __bits(b.__bits) {}
	void clear() { __bits.clear(); __size = 0; }
	size_t size() const { return __size; }
	void resize(int n) {
		__size = n;
		__bits.assign(__size_to_vector_size(n), 0);
	}
	bool test(size_t n) {
		uchar&c = __bits[n >> 3];
		size_t i = n & 7;
		return (c >> i) & 1;
	}
	bool set(size_t n) {
		uchar&c = __bits[n >> 3];
		size_t i = n & 7;
		if ((c >> i) & 1) return false;
		c |= uchar(1) << i;
		return true;
	}
	bool reset(size_t n) {
		uchar&c = __bits[n >> 3];
		size_t i = n & 7;
		if (~(c >> i) & 1) return false;
		c &= ~(uchar(1) << i);
		return true;
	}
	void flip(size_t n) {
		uchar&c = __bits[n >> 3];
		size_t i = n & 7;
		c ^= uchar(1) << i;
	}
	void set() {
		for (size_t i = 0; i < __bits.size(); ++i)
			__bits[i] = 255;
	}
	void reset() {
		for (size_t i = 0; i < __bits.size(); ++i)
			__bits[i] = 0;
	}
	void flip() {
		for (size_t i = 0; i < __bits.size(); ++i)
			__bits[i] ^= 255;
	}
	std::string to_string() const {
		std::string ret;
		for (size_t i = 0; i < __bits.size(); ++i) {
			const uchar& c = __bits[i];
			for (size_t j = 0; j < 8; ++j)
				ret += (c >> j & 1) ? "1" : "0";
		}
		ret.resize(__size);
		return ret;
	}
	bit_set& operator = (const bit_set& rhs) {
		__size = rhs.__size;
		__bits = rhs.__bits;
		return *this;
	}
};

inline std::ostream& operator<< (std::ostream& os, const bit_set& bs) {
	return os << bs.to_string();
}

/* eof */
#endif
