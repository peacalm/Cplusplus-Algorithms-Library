/*
 * bit-operation header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-7-12
 */

#ifndef __BIT_OPERATION_H__
#define __BIT_OPERATION_H__

#include <cassert>
#include <vector>


// set the i-th(0 started) bit.
inline int _1(int i) { assert(i < 32); return 1 << i; }
// set rightmost i bits.
inline int _7(int i) { assert(i < 32); return (1 << i) - 1; }
// 64bit _1 and _7
inline long long _1L(int i) { assert(i < 64); return 1LL << i; }
inline long long _7L(int i) { assert(i < 64); return (1LL << i) - 1; }

// inverse function of _1(i) or _1L(i), put in _1(i) or _1L(i) returns i
template<typename T> inline int i_1(T x) {
	assert((x & x - 1) == 0);
	int ret = 0;
	for (int i = sizeof(T) << 2; i; i >>= 1) if (x >> i) { ret += i; x >>= i; }
	return ret;
}

// get the least siginificant bit 1 
template<typename T> inline T lowbit(T x) { return x & (~x + 1); }
// test the i-th(0 started) bit of x, is 1 or not.
template<typename T> inline bool testbit(T x, int i) { return (bool)(x & (T(1) << i)); }
// set the i-th bit, if the bit is already set, return false, else set it then return true.
template<typename T> inline bool setbit(T& x, int i) { return (x & (T(1) << i)) ? false : (x |= (T(1) << i), true); }
// reset the i-th bit, if the bit is already reset, return false, else reset it then return true.
template<typename T> inline bool resetbit(T& x, int i) { return (x & (T(1) << i)) ? (x &= ~(T(1) << i), true) : false; }

// count 1 bits
template<typename T>
inline int cntbit(T x) {
	int len = sizeof(T) << 3;
	x = ((x & 0xaaaaaaaaaaaaaaaa) >> 1) + (x & 0x5555555555555555);
	x = ((x & 0xcccccccccccccccc) >> 2) + (x & 0x3333333333333333);
	x = ((x & 0xf0f0f0f0f0f0f0f0) >> 4) + (x & 0x0f0f0f0f0f0f0f0f);
	if (len >= 16) x = ((x & 0xff00ff00ff00ff00) >> 8) + (x & 0x00ff00ff00ff00ff);
	if (len >= 32) x = ((x & 0xffff0000ffff0000) >> 16) + (x & 0x0000ffff0000ffff);
	if (len >= 64) x = ((x & 0xffffffff00000000) >> 32) + (x & 0x00000000ffffffff);
	return x;
}

// reverse bits
template<typename T>
inline T reversebit(T x) {
	int len = sizeof(T) << 3;
	x = ((x & 0xaaaaaaaaaaaaaaaa) >> 1) | ((x & 0x5555555555555555) << 1);
	x = ((x & 0xcccccccccccccccc) >> 2) | ((x & 0x3333333333333333) << 2);
	x = ((x & 0xf0f0f0f0f0f0f0f0) >> 4) | ((x & 0x0f0f0f0f0f0f0f0f) << 4);
	if (len >= 16) x = ((x & 0xff00ff00ff00ff00) >> 8) | ((x & 0x00ff00ff00ff00ff) << 8);
	if (len >= 32) x = ((x & 0xffff0000ffff0000) >> 16) | ((x & 0x0000ffff0000ffff) << 16);
	if (len >= 64) x = ((x & 0xffffffff00000000) >> 32) | ((x & 0x00000000ffffffff) << 32);
	return x;
}


// cntbit and reversebit specialized for int, long long
inline int cntbit(int x) {
	x = ((x & 0xaaaaaaaa) >> 1) + (x & 0x55555555);
	x = ((x & 0xcccccccc) >> 2) + (x & 0x33333333);
	x = ((x & 0xf0f0f0f0) >> 4) + (x & 0x0f0f0f0f);
	x = ((x & 0xff00ff00) >> 8) + (x & 0x00ff00ff);
	x = ((x & 0xffff0000) >> 16) + (x & 0x0000ffff);
	return x;
}
inline int cntbit(long long x) {
	x = ((x & 0xaaaaaaaaaaaaaaaa) >> 1) + (x & 0x5555555555555555);
	x = ((x & 0xcccccccccccccccc) >> 2) + (x & 0x3333333333333333);
	x = ((x & 0xf0f0f0f0f0f0f0f0) >> 4) + (x & 0x0f0f0f0f0f0f0f0f);
	x = ((x & 0xff00ff00ff00ff00) >> 8) + (x & 0x00ff00ff00ff00ff);
	x = ((x & 0xffff0000ffff0000) >> 16) + (x & 0x0000ffff0000ffff);
	x = ((x & 0xffffffff00000000) >> 32) + (x & 0x00000000ffffffff);
	return int(x);
}
inline int reversebit(int x) {
	x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
	x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2);
	x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
	x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
	x = ((x & 0xffff0000) >> 16) | ((x & 0x0000ffff) << 16);
	return x;
}
inline long long reversebit(long long x) {
	x = ((x & 0xaaaaaaaaaaaaaaaa) >> 1) | ((x & 0x5555555555555555) << 1);
	x = ((x & 0xcccccccccccccccc) >> 2) | ((x & 0x3333333333333333) << 2);
	x = ((x & 0xf0f0f0f0f0f0f0f0) >> 4) | ((x & 0x0f0f0f0f0f0f0f0f) << 4);
	x = ((x & 0xff00ff00ff00ff00) >> 8) | ((x & 0x00ff00ff00ff00ff) << 8);
	x = ((x & 0xffff0000ffff0000) >> 16) | ((x & 0x0000ffff0000ffff) << 16);
	x = ((x & 0xffffffff00000000) >> 32) | ((x & 0x00000000ffffffff) << 32);
	return x;
}


//// combinations and sets

// traverse the sebsets of a bitset formed in integer s
#define SUBSETS(i, s)         for (long long i = 0, _SWITCH_ = 0; _SWITCH_ ^= i == 0 ; i = (i - s) & s)
#define rSUBSETS(i, s)        for (long long i = s, _SWITCH_ = 0; _SWITCH_ ^= i == s ; i = (i - 1) & s)

// subsets of a betset formed in integer s
template<typename T> inline std::vector<T> subsets(T s) {
	std::vector<T> ret;
	for (T i = 0; ; i = (i - s) & s) {
		ret.push_back(i);
		if (i == s) break;
	}
	return ret;
}

// Gosper's hack : to get the next higher number with the same number of 1 bits.
// colex next
template<typename T> inline bool Gosper_next(T& x) {
	if (!x) return false;
	unsigned long long lowbit = x & (~x + 1);
	unsigned long long ripple = lowbit + x;
	if (!ripple) return false;
	x = ripple | (((x ^ ripple) >> 2) / lowbit);
	return true;
}
// colex previous
template<typename T> inline bool Gosper_prev(T& x) {
	if (!x) return false;
	x = ~x;
	unsigned long long lowbit = x & (~x + 1);
	unsigned long long ripple = lowbit + x;
	if (!ripple) { x = ~x; return false; }
	x = ripple | (((x ^ ripple) >> 2) / lowbit);
	x = ~x;
	return true;
}

// reference: Frank Ruskey, Aaron Williams, The Coolest Way to Generate Combinations
// cool-lex next
template<typename T> inline bool Ruskey_Williams_next(T& x) {
	if (x == 0 || x == (T)(-1)) return false;
	T ripple = x & (x + 1);
	T lowmask = ripple ^ (ripple - 1);
	if (ripple != 0 && lowmask == (T)(-1)) return false;
	x = x + (x & lowmask) - (x & (lowmask + 1) ? lowmask : 0);
	return true;
}
// cool-lex previous
template<typename T> inline bool Ruskey_Williams_prev(T& x) {
	if (x == 0 || x == (T)(-1)) return false;
	T t = x | 1;
	unsigned long long ripple = t & (t + 1);
	if (x == t && ripple == 0) return false;
	unsigned long long lowmask = ripple ^ (ripple - 1);
	unsigned long long low = x & lowmask;
	x = x - (low >> 1) + (x & 1 ? lowmask >> 1 : 0);
	return true;
}



/* eof */
#endif
