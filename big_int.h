/*
 * big-int header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-5-7
 * last edit on 2016-7-14, add operator ++, --
 */


#ifndef __BIG_INT_H__
#define __BIG_INT_H__

#include "cil_config.h"
#include <cassert>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

class big_int {
	static const int MAX_LEN = 25; // mutable, upper bound of big_int
	static const int MOD = 10000;
	int sign;
	int len;
	int a[MAX_LEN];
	void positive_constructor(unsigned long long);
	void negative_constructor(long long);
	big_int& left_shift();
public:
	big_int();
	big_int(int);
	big_int(unsigned int);
	big_int(long long);
	big_int(unsigned long long);
	big_int(const char *);
	big_int(const string &);
	big_int(const big_int &);
	~big_int();
	
	big_int operator -() const;
	big_int operator + (const big_int &) const;
	big_int operator - (const big_int &) const;
	big_int operator * (const big_int &) const;
	big_int operator / (const big_int &) const;
	big_int operator % (const big_int &) const;
	big_int& operator = (const big_int &);
	big_int& operator += (const big_int &);
	big_int& operator -= (const big_int &);
	big_int& operator *= (const big_int &);
	big_int& operator /= (const big_int &);
	big_int& operator %= (const big_int &);
	big_int& operator ++();
	big_int& operator --();
	big_int operator ++(int);
	big_int operator --(int);

	bool operator == (const big_int &) const;
	bool operator != (const big_int &) const;
	bool operator < (const big_int &) const;
	bool operator <= (const big_int &) const;
	bool operator > (const big_int &) const;
	bool operator >= (const big_int &) const;

	void clear();
	int get_sign() const;
	int get_length() const;
	int operator [](int i) const;
	big_int abs() const;
	string to_string() const;

	void print();
	void println();
	friend istream& operator >> (istream &, big_int &);
	friend ostream& operator << (ostream &, const big_int &);
};
typedef big_int bint;

// implementations 
inline void big_int::positive_constructor(unsigned long long b){
	sign = 1;
	len = 0;
	memset(a, 0, sizeof(a));
	while (b >= MOD) {
		a[len++] = b % MOD;
		b /= MOD;
	}
	a[len++] = (int)(b);
}
inline void big_int::negative_constructor(long long b){
	sign = -1;
	len = 0;
	memset(a, 0, sizeof(a));
	while (b <= -MOD) {
		long long rem = b % MOD;
		a[len++] = (int)(rem >= 0 ? rem : -rem);
		b /= MOD;
	}
	a[len++] = (int)(-b);
}
inline big_int& big_int::left_shift() {
	if (len == 1 && a[0] == 0) return *this;
	for (int i = len - 1; i >= 0; --i) a[i + 1] = a[i];
	a[0] = 0; ++len;
	return *this;
}
// constructors
inline big_int::big_int() :sign(1), len(1) { memset(a, 0, sizeof(a)); }
inline big_int::big_int(int b) {
	b >= 0 ? positive_constructor(b) : negative_constructor(b);
}
inline big_int::big_int(unsigned int b) {
	positive_constructor(b);
}
inline big_int::big_int(long long b) {
	b >= 0 ? positive_constructor(b) : negative_constructor(b);
}
inline big_int::big_int(unsigned long long b) {
	positive_constructor(b);
}
inline big_int::big_int(const char *b) {
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
inline big_int::big_int(const string &b) {
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
inline big_int::big_int(const big_int &b) {
	sign = b.sign;
	len = b.len;
	memcpy(a, b.a, sizeof(a));
}
inline big_int::~big_int() {}


// arithmetic operators
inline big_int big_int::operator -() const {
	big_int ret = *this;
	if (ret.len == 1 && ret.a[0] == 0) { ret.sign = 1; }
	else ret.sign *= -1;
	return ret;
}
inline big_int big_int::operator + (const big_int &b) const {
	if (sign == b.sign) {
		big_int ret;
		ret.len = 0;
		ret.sign = sign;
		int up = 0;
		for (int i = 0; i < len || i < b.len; ++i) {
			int sum = up;
			if (i < len) sum += a[i];
			if (i < b.len) sum += b.a[i];
			up = sum / MOD;
			sum %= MOD;
			ret.a[ret.len++] = sum;
		}
		if (up != 0) ret.a[ret.len++] = up;
		return ret;
	}
	else {
		if (sign == 1) return *this - (-b);
		else return b - (-(*this));
	}
}
inline big_int big_int::operator - (const big_int &b)const {
	if (sign == b.sign) {
		if (sign == -1) return -((-*this) - (-b));
		if (*this == b) return big_int(0);
		if (*this < b) return -(b - *this);
		
		big_int ret;
		ret.len = 0;
		int up = 0;
		for (int i = 0; i < len; ++i) {
			int diff = a[i] - up;
			up = 0;
			if (i < b.len) diff -= b.a[i];
			if (diff < 0) { diff += MOD; ++up; }
			ret.a[ret.len++] = diff;
		}
		while (ret.len > 1 && ret.a[ret.len - 1] == 0) --ret.len;
		return ret;
	}
	else {
		if (sign == 1) return *this + (-b);
		else return -((-(*this)) + b);
	}
}
inline big_int big_int::operator * (const big_int &b)const {
	if (b.len == 1 && b.a[0] == 0) return big_int(0);
	big_int ret;
	ret.len = 0;
	ret.sign = sign * b.sign;
	int up = 0;
	int i = 0, j = 0;
	for (i = 0; i < len; ++i) {
		for (j = 0; j < b.len; ++j) {
			ret.a[i + j] = a[i] * b.a[j] + up + ret.a[i + j];
			up = ret.a[i + j] / MOD;
			ret.a[i + j] %= MOD;
		}
		if (up) { ret.a[i + j] = up; up = 0; }
	}
	ret.len = i + j;
	while (ret.a[ret.len - 1] == 0 && ret.len > 1) --ret.len;
	return ret;
}
inline big_int big_int::operator / (const big_int &b) const {
	big_int ret;
	ret.sign = sign / b.sign;
	big_int down = 0;
	for (int i = len - 1; i >= 0; --i) {
		down = down.left_shift() + big_int(a[i]);
		int l = 0, r = MOD - 1;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (b.abs() * mid > down) r = mid - 1;
			else l = mid;
		}
		down -= b.abs() * l;
		ret.a[i] = l;
	}
	ret.len = len;
	while (ret.a[ret.len - 1] == 0 && ret.len > 1) --ret.len;
	if (ret.len == 1 && ret.a[0] == 0) ret.sign = 1;
	return ret;
}
inline big_int big_int::operator % (const big_int &b)const {
	big_int down;
	for (int i = len - 1; i >= 0; --i) {
		down = down.left_shift() + big_int(a[i]);
		int l = 0, r = MOD - 1;
		while (l < r) {
			int mid = (l + r + 1) >> 1;
			if (b.abs() * mid > down) r = mid - 1;
			else l = mid;
		}
		down -= b.abs() * l;
	}
	if (down != 0 && sign == -1) down.sign = -1;
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

inline big_int& big_int::operator ++() { return *this += big_int(1); }
inline big_int& big_int::operator --() { return *this -= big_int(1); }
inline big_int big_int::operator ++(int) { big_int ret = *this; *this += big_int(1); return ret; }
inline big_int big_int::operator --(int) { big_int ret = *this; *this -= big_int(1); return ret; }

// compare operators
inline bool big_int::operator == (const big_int &b) const {
	return sign == b.sign && len == b.len && !memcmp(a, b.a, sizeof(a));
}
inline bool big_int::operator != (const big_int &b) const {
	return sign != b.sign || len != b.len || memcmp(a, b.a, sizeof(a));
}
inline bool big_int::operator < (const big_int &b) const {
	if (sign != b.sign) return sign < b.sign;
	int reverse = sign == 1 ? 0 : 1;
	int ret = -1;
	if (len != b.len) {
		ret = len < b.len;
	}
	else {
		for (int i = len - 1; i >= 0; --i) if (a[i] != b.a[i]) {
			ret = a[i] < b.a[i];
			break;
		}
	}
	if (ret == -1) return false;
	return bool(ret ^ reverse);
}
inline bool big_int::operator <= (const big_int &b) const { return *this < b || *this == b; }
inline bool big_int::operator > (const big_int &b) const { return b < *this; }
inline bool big_int::operator >= (const big_int &b) const { return b <= *this; }

inline void big_int::clear() { sign = 1; len = 1; memset(a, 0, sizeof(a));}
inline int big_int::get_sign() const { return sign; }
inline int big_int::get_length() const { return len; }
inline int big_int::operator [](int i) const { assert(i >= 0 && i < len); return a[i]; }
inline big_int big_int::abs() const { return sign > 0 ? *this : -*this; }
inline string big_int::to_string() const {
	string ret;
	if (sign == -1) ret += "-";
	char buf[10];
	sprintf(buf, "%d", a[len - 1]);
	ret += string(buf);
	for (int i = len - 2; i >= 0; --i) {
		sprintf(buf, "%04d", a[i]);
		ret += string(buf);
	}
	return ret;
}
inline void big_int::print() {
	if (sign == -1) putchar('-');
	assert(len >= 1 && len < MAX_LEN);
	printf("%d", a[len - 1]);
	for (int i = len - 2; i >= 0; --i) printf("%04d", a[i]);
}
inline void big_int::println() { print(); putchar('\n'); }

// friend functions, iostream
inline istream& operator >> (istream &is, big_int &b) { string s; is >> s; b = big_int(s); return is; }
inline ostream& operator << (ostream &os, const big_int &b) { os << b.to_string(); return os; }

// operators overwrite
big_int operator + (int a, const big_int& b) { return big_int(a) + b; }
big_int operator + (unsigned int a, const big_int& b) { return big_int(a) + b; }
big_int operator + (long long a, const big_int& b) { return big_int(a) + b; }
big_int operator + (unsigned long long a, const big_int& b) { return big_int(a) + b; }
big_int operator - (int a, const big_int& b) { return big_int(a) - b; }
big_int operator - (unsigned int a, const big_int& b) { return big_int(a) - b; }
big_int operator - (long long a, const big_int& b) { return big_int(a) - b; }
big_int operator - (unsigned long long a, const big_int& b) { return big_int(a) - b; }
big_int operator * (int a, const big_int& b) { return big_int(a) * b; }
big_int operator * (unsigned int a, const big_int& b) { return big_int(a) * b; }
big_int operator * (long long a, const big_int& b) { return big_int(a) * b; }
big_int operator * (unsigned long long a, const big_int& b) { return big_int(a) * b; }
big_int operator / (int a, const big_int& b) { return big_int(a) / b; }
big_int operator / (unsigned int a, const big_int& b) { return big_int(a) / b; }
big_int operator / (long long a, const big_int& b) { return big_int(a) / b; }
big_int operator / (unsigned long long a, const big_int& b) { return big_int(a) / b; }
big_int operator % (int a, const big_int& b) { return big_int(a) % b; }
big_int operator % (unsigned int a, const big_int& b) { return big_int(a) % b; }
big_int operator % (long long a, const big_int& b) { return big_int(a) % b; }
big_int operator % (unsigned long long a, const big_int& b) { return big_int(a) % b; }

// ================================================================== //
// utility functions out of the class

inline big_int abs(const big_int &x) { return x.get_sign() > 0 ? x : -x; }

inline string to_string(const big_int &x) {
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
