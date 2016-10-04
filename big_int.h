/*
 * big-int header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-5-7
 * last edit on 2016-7-30
 * last edit on 2016-10-4, overwrite +,-,*,/,%,==,!=,<,>,<=,>= into friend.
 */


#ifndef __BIG_INT_H__
#define __BIG_INT_H__

#include "cil_config.h"
#include <cassert>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>

class big_int {
	static const int MAX_LEN = 100; // mutable, upper bound of big_int 10^(4*MAX_LEN)
	static const int MOD = 10000;
	int sign;
	int len;
	int a[MAX_LEN];
	void positive_constructor(unsigned long long);
	void negative_constructor(long long);
	big_int& left_shift();
public:
	big_int();
	big_int(short);
	big_int(unsigned short);
	big_int(int);
	big_int(unsigned int);
	big_int(long);
	big_int(unsigned long);
	big_int(long long);
	big_int(unsigned long long);
	big_int(const char*);
	big_int(const std::string&);
	big_int(const big_int&);
	~big_int();
	
	big_int operator - () const;
	big_int& operator ++ ();
	big_int& operator -- ();
	big_int operator ++ (int);
	big_int operator -- (int);

	friend const big_int operator + (const big_int&, const big_int&);
	friend const big_int operator - (const big_int&, const big_int&);
	friend const big_int operator * (const big_int&, const big_int&);
	friend const big_int operator / (const big_int&, const big_int&);
	friend const big_int operator % (const big_int&, const big_int&);

	big_int& operator = (const big_int&);
	big_int& operator += (const big_int&);
	big_int& operator -= (const big_int&);
	big_int& operator *= (const big_int&);
	big_int& operator /= (const big_int&);
	big_int& operator %= (const big_int&);

	friend bool operator == (const big_int&, const big_int&);
	friend bool operator != (const big_int&, const big_int&);
	friend bool operator < (const big_int&, const big_int&);
	friend bool operator <= (const big_int&, const big_int&);
	friend bool operator > (const big_int&, const big_int&);
	friend bool operator >= (const big_int&, const big_int&);

	void clear();
	big_int& reverse();
	int get_sign() const;
	int get_length() const;
	int operator [] (int i) const;
	big_int abs() const;
	std::string to_string() const;

	void print() const;
	void println() const;
};
typedef big_int bint;

// implementations 
inline void big_int::positive_constructor(unsigned long long b){
	sign = 1;
	len = 0;
	while (b >= MOD) {
		a[len++] = (int)(b % MOD);
		b /= MOD;
	}
	a[len++] = (int)(b);
	for (int i = len; i < MAX_LEN; ++i) a[i] = 0;
}
inline void big_int::negative_constructor(long long b){
	sign = -1;
	len = 0;
	while (b <= -MOD) {
		long long rem = b % MOD;
		a[len++] = (int)(rem >= 0 ? rem : -rem);
		b /= MOD;
	}
	a[len++] = (int)(-b);
	for (int i = len; i < MAX_LEN; ++i) a[i] = 0;
}
inline big_int& big_int::left_shift() {
	if (len == 1 && a[0] == 0) return *this;
	assert(len < MAX_LEN);
	for (int i = len - 1; i >= 0; --i) a[i + 1] = a[i];
	a[0] = 0; ++len;
	return *this;
}

// constructors
inline big_int::big_int() : sign(1), len(1) { 
	memset(a, 0, sizeof(a));
}
inline big_int::big_int(short b) {
	b >= 0 ? positive_constructor(b) : negative_constructor(b);
}
inline big_int::big_int(unsigned short b) {
	positive_constructor(b);
}
inline big_int::big_int(int b) {
	b >= 0 ? positive_constructor(b) : negative_constructor(b);
}
inline big_int::big_int(unsigned int b) {
	positive_constructor(b);
}
inline big_int::big_int(long b) {
	b >= 0 ? positive_constructor(b) : negative_constructor(b);
}
inline big_int::big_int(unsigned long b) {
	positive_constructor(b);
}
inline big_int::big_int(long long b) {
	b >= 0 ? positive_constructor(b) : negative_constructor(b);
}
inline big_int::big_int(unsigned long long b) {
	positive_constructor(b);
}
inline big_int::big_int(const char* b) {
	sign = 1;
	len = 0;
	memset(a, 0, sizeof(a));

	int l = 0;
	int r = int(strlen(b));
	if (l == r) { len = 1; return; }

	if (b[l] == '-') { sign = -1; ++l; }
	else if (b[l] == '+') { ++l; }
	while (b[l] == '0') ++l;
	if (l == r) { len = 1; return; }

	int v = 0;
	int power = 1;
	for (int i = r - 1; i >= l; --i) {
		assert(b[i] >= '0' && b[i] <= '9');
		v = (b[i] - '0') * power + v;
		power *= 10;
		if (power == MOD) {
			a[len++] = v;
			v = 0;
			power = 1;
		}
	}
	if (v != 0) a[len++] = v;
}
inline big_int::big_int(const std::string& b) {
	sign = 1;
	len = 0;
	memset(a, 0, sizeof(a));

	int l = 0;
	int r = int(b.size());
	if (l == r) { len = 1; return; }

	if (b[l] == '-') { sign = -1; ++l; }
	else if (b[l] == '+') { ++l; }
	while (b[l] == '0') ++l;
	if (l == r) { len = 1; return; }

	int v = 0;
	int power = 1;
	for (int i = r - 1; i >= l; --i) {
		assert(b[i] >= '0' && b[i] <= '9');
		v = (b[i] - '0') * power + v;
		power *= 10;
		if (power == MOD) {
			a[len++] = v;
			v = 0;
			power = 1;
		}
	}
	if (v != 0) a[len++] = v;
}
inline big_int::big_int(const big_int& b) {
	sign = b.sign;
	len = b.len;
	memcpy(a, b.a, sizeof(a));
}
inline big_int::~big_int() {}


// arithmetic operators and assignments
inline big_int big_int::operator - () const {
	big_int ret = *this;
	if (ret.len == 1 && ret.a[0] == 0) { ret.sign = 1; }
	else ret.sign *= -1;
	return ret;
}
inline big_int& big_int::operator ++() { 
	return *this += big_int(1);
}
inline big_int& big_int::operator --() { 
	return *this -= big_int(1);
}
inline big_int big_int::operator ++(int) { 
	big_int ret = *this;
	*this += big_int(1);
	return ret;
}
inline big_int big_int::operator --(int) { 
	big_int ret = *this;
	*this -= big_int(1);
	return ret;
}
inline const big_int operator + (const big_int& lhs, const big_int& rhs) {
	if (lhs.sign == rhs.sign) {
		big_int ret;
		ret.len = 0;
		ret.sign = lhs.sign;
		int up = 0;
		for (int i = 0; i < lhs.len || i < rhs.len; ++i) {
			int sum = up;
			if (i < lhs.len) sum += lhs.a[i];
			if (i < rhs.len) sum += rhs.a[i];
			up = sum / lhs.MOD;
			sum %= lhs.MOD;
			ret.a[ret.len++] = sum;
		}
		if (up != 0) ret.a[ret.len++] = up;
		return ret;
	}
	else {
		if (lhs.sign == 1) return lhs - (-rhs);
		else return rhs - (-lhs);
	}
}
inline const big_int operator - (const big_int& lhs, const big_int& rhs) {
	if (lhs.sign == rhs.sign) {
		if (lhs.sign == -1) return -((-lhs) - (-rhs));
		if (lhs == rhs) return big_int(0);
		if (lhs < rhs) return -(rhs - lhs);
		
		big_int ret;
		ret.len = 0;
		int up = 0;
		for (int i = 0; i < lhs.len; ++i) {
			int diff = lhs.a[i] - up;
			up = 0;
			if (i < rhs.len) diff -= rhs.a[i];
			if (diff < 0) { diff += lhs.MOD; ++up; }
			ret.a[ret.len++] = diff;
		}
		while (ret.len > 1 && ret.a[ret.len - 1] == 0) --ret.len;
		return ret;
	}
	else {
		if (lhs.sign == 1) return lhs + (-rhs);
		else return -((-lhs) + rhs);
	}
}
inline const big_int operator * (const big_int& lhs, const big_int& rhs) {
	if (rhs.len == 1 && rhs.a[0] == 0) return big_int(0);
	big_int ret;
	ret.len = 0;
	ret.sign = lhs.sign * rhs.sign;
	int up = 0;
	int i = 0, j = 0;
	for (i = 0; i < lhs.len; ++i) {
		for (j = 0; j < rhs.len; ++j) {
			ret.a[i + j] = lhs.a[i] * rhs.a[j] + up + ret.a[i + j];
			up = ret.a[i + j] / lhs.MOD;
			ret.a[i + j] %= lhs.MOD;
		}
		if (up) { ret.a[i + j] = up; up = 0; }
	}
	ret.len = i + j;
	while (ret.a[ret.len - 1] == 0 && ret.len > 1) --ret.len;
	return ret;
}
inline const big_int operator / (const big_int& lhs, const big_int& rhs) {
	big_int ret;
	ret.sign = lhs.sign / rhs.sign;
	big_int down = 0;
	for (int i = lhs.len - 1; i >= 0; --i) {
		down = down.left_shift() + big_int(lhs.a[i]);
		int l = 0, r = lhs.MOD - 1;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (rhs.abs() * mid > down) r = mid - 1;
			else l = mid;
		}
		down -= rhs.abs() * l;
		ret.a[i] = l;
	}
	ret.len = lhs.len;
	while (ret.a[ret.len - 1] == 0 && ret.len > 1) --ret.len;
	if (ret.len == 1 && ret.a[0] == 0) ret.sign = 1;
	return ret;
}
inline const big_int operator % (const big_int& lhs, const big_int& rhs) {
	big_int down;
	for (int i = lhs.len - 1; i >= 0; --i) {
		down = down.left_shift() + big_int(lhs.a[i]);
		int l = 0, r = lhs.MOD - 1;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (rhs.abs() * mid > down) r = mid - 1;
			else l = mid;
		}
		down -= rhs.abs() * l;
	}
	if (down != 0 && lhs.sign == -1) down.sign = -1;
	return down;
}

inline big_int& big_int::operator = (const big_int &b) {
	sign = b.sign;
	len = b.len;
	memcpy(a, b.a, sizeof(a));
	return *this;
}
inline big_int& big_int::operator += (const big_int &b) {
	return *this = *this + b;
}
inline big_int& big_int::operator -= (const big_int &b) {
	return *this = *this - b;
}
inline big_int& big_int::operator *= (const big_int &b) {
	return *this = *this * b;
}
inline big_int& big_int::operator /= (const big_int &b) {
	return *this = *this / b;
}
inline big_int& big_int::operator %= (const big_int &b) {
	return *this = *this % b;
}

// compare operators
inline bool operator == (const big_int& lhs, const big_int& rhs) {
	return lhs.sign == rhs.sign && lhs.len == rhs.len && !memcmp(lhs.a, rhs.a, sizeof(lhs.a[0]) * lhs.len);
}
inline bool operator != (const big_int& lhs, const big_int& rhs) {
	return lhs.sign != rhs.sign || lhs.len != rhs.len || memcmp(lhs.a, rhs.a, sizeof(lhs.a[0]) * lhs.len);
}
inline bool operator < (const big_int& lhs, const big_int& rhs) {
	if (lhs.sign != rhs.sign) return lhs.sign < rhs.sign;
	int reverse = lhs.sign == 1 ? 0 : 1;
	int ret = -1;
	if (lhs.len != rhs.len) {
		ret = int(lhs.len < rhs.len);
	}
	else {
		for (int i = lhs.len - 1; i >= 0; --i) if (lhs.a[i] != rhs.a[i]) {
			ret = int(lhs.a[i] < rhs.a[i]);
			break;
		}
	}
	if (ret == -1) return false;
	return bool(ret ^ reverse);
}
inline bool operator <= (const big_int& lhs, const big_int& rhs) {
	return lhs < rhs || lhs == rhs;
}
inline bool operator > (const big_int& lhs, const big_int& rhs) {
	return rhs < lhs;
}
inline bool operator >= (const big_int& lhs, const big_int& rhs) {
	return rhs <= lhs;
}

// utility member functions
inline void big_int::clear() { 
	sign = 1;
	len = 1;
	memset(a, 0, sizeof(a));
}
inline big_int& big_int::reverse() {
	if (len > 1 || a[0] > 0) sign *= -1;
	return *this;
}
inline int big_int::get_sign() const {
	return sign;
}
inline int big_int::get_length() const {
	return len;
}
inline int big_int::operator [] (int i) const {
	assert(i >= 0 && i < len);
	return a[i];
}
inline big_int big_int::abs() const {
	return sign > 0 ? *this : -*this;
}
inline std::string big_int::to_string() const {
	std::string ret;
	if (sign == -1) ret += "-";
	char buf[10];
	sprintf(buf, "%d", a[len - 1]);
	ret += std::string(buf);
	for (int i = len - 2; i >= 0; --i) {
		sprintf(buf, "%04d", a[i]);
		ret += std::string(buf);
	}
	return ret;
}

// input/output functions
inline void big_int::print() const {
	if (sign == -1) putchar('-');
	assert(len >= 1 && len < MAX_LEN);
	printf("%d", a[len - 1]);
	for (int i = len - 2; i >= 0; --i) printf("%04d", a[i]);
}
inline void big_int::println() const {
	print(); putchar('\n');
}
inline std::istream& operator >> (std::istream& is, big_int& b) {
	std::string s;
	is >> s;
	b = big_int(s);
	return is;
}
inline std::ostream& operator << (std::ostream& os, const big_int& b) {
	os << b.to_string();
	return os;
}

// ================================================================== //
// utility non-member functions

inline big_int abs(const big_int &x) { return x.get_sign() > 0 ? x : -x; }

inline std::string to_string(const big_int &x) {
	return x.to_string();
}

// return floor(sqrt(x)), that is the greatest integer whose sqrare is less than x.
inline big_int sqrt(const big_int &x) {
	big_int l = 0, r = x;
	while (l < r) {
		big_int mid = (l + r + 1) / 2;
		big_int t = mid * mid;
		if (t == x) return mid;
		if (t < x) l = mid;
		else r = mid - 1;
	}
	return l;
}


/* eof */
#endif
