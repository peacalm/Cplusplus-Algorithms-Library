/*
 * io header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-7-14
 */

#ifndef __IO_H__
#define __IO_H__

#include "cil_config.h"
#include <cstdio>
#include <iostream>

// read integer types
template<typename T> inline bool RD(T& v) { char c; bool n; while (c = getchar(), c != '-' && (c < '0' || c > '9')) if (c == EOF) return false; if (c == '-') { n = true; v = 0; } else { n = false; v = c - '0'; } while (c = getchar(), c >= '0' && c <= '9') v = (v << 3) + (v << 1) + c - '0'; if (n) v *= -1; return true; }
template<typename A, typename ...Args> inline bool RD(A& a, Args&... rest) { return RD(a) && RD(rest...); }
inline int RD() { int v; RD(v); return v; }
#define RDn(a, l, r)          { for (int _i_ = l; _i_ < r; ++_i_) RD((a)[_i_]); }
#define RDnm(a, b, c, d, e)   { for (int __i__ = b; __i__ < c; ++__i__) RDn(a[__i__], d, e) }

// read integer types with buffer
inline char getchar_buffered() { static char _BUF_[1 << 15], *_HEAD_ = _BUF_, *_TAIL_ = _BUF_; return _HEAD_ == _TAIL_ && (_TAIL_ = (_HEAD_ = _BUF_) + fread(_BUF_, 1, 1 << 15, stdin), _HEAD_ == _TAIL_) ? EOF : *_HEAD_++; }
template<typename T> inline bool RDB(T& v) { char c; bool n; while (c = getchar_buffered(), c != '-' && (c < '0' || c > '9')) if (c == EOF) return false; if (c == '-') { n = true; v = 0; } else { n = false; v = c - '0'; } while (c = getchar_buffered() - '0', c >= 0 && c <= 9) v = (v << 3) + (v << 1) + c; if (n) v *= -1; return true; }
template<typename A, typename ...Args> inline bool RDB(A& a, Args&... rest) { return RDB(a) && RDB(rest...); }
inline int RDB() { int v; RDB(v); return v; }
#define RDBn(a, l, r)         { for (int _i_ = l; _i_ < r; ++_i_) RDB((a)[_i_]); }
#define RDBnm(a, b, c, d, e)  { for (int __i__ = b; __i__ < c; ++__i__) RDBn(a[__i__], d, e) }

// write integer types
template<typename T> inline void _WR(T a) { if (a < 0) { putchar('-'); a *= -1; } T t = a / 10; if (t) _WR(t); putchar(a - (t << 1) - (t << 3) + '0'); }
template<typename T> inline void WR_(const T&a) { _WR(a); putchar(' '); }
template<typename T> inline void WR(const T&a) { _WR(a); putchar('\n'); }
template<typename A, typename ...Args> inline void _WR(const A& a, const Args&... rest) { WR_(a); _WR(rest...); }
template<typename A, typename ...Args> inline void WR_(const A& a, const Args&... rest) { WR_(a); WR_(rest...); }
template<typename A, typename ...Args> inline void WR (const A& a, const Args&... rest) { WR_(a); WR(rest...); }
#define WRn(a, l, r)          { for (int _i_ = l; _i_ < r - 1; ++_i_) WR_((a)[_i_]); if(r > 0) WR((a)[r - 1]); }
#define WRnm(a, b, c, d, e)   { for (int __i__ = b; __i__ < c; ++__i__) WRn(a[__i__], d, e) }

// quick IO for any type using cin, cout
template <typename A> inline std::istream &IN(A& a) { return std::cin >> a; }
template <typename A, typename ...Args> inline std::istream& IN(A& a, Args&... rest) { std::cin >> a; return IN(rest...); }
#define INn(a, l, r)          { for (int _i_ = l; _i_ < r; ++_i_) IN(a[_i_]); }
#define INnm(a, b, c, d, e)   { for (int __i__ = b; __i__ < c; ++__i__) INn(a[__i__], d, e) }

inline std::ostream& OUT() { return std::cout << std::endl; }
template <typename A> inline std::ostream& _OUT(const A &a) { return std::cout << a; }
template <typename A, typename...Args> inline std::ostream& _OUT(const A &a, const Args&... rest) { std::cout << a << " "; return _OUT(rest...); }
template <typename...Args> inline std::ostream& OUT_(const Args&... args) { _OUT(args...); return std::cout << " "; }
template <typename...Args> inline std::ostream& OUT(const Args&... args) { _OUT(args...); return std::cout << std::endl; }
#define OUTn(a, l, r)         { for (int _i_ = l; _i_ < r - 1; ++_i_) OUT_((a)[_i_]); if(r > 0) OUT((a)[r - 1]); }
#define OUTnm(a, b, c, d, e)  { for (int __i__ = b; __i__ < c; ++__i__) OUTn(a[__i__], d, e) }


/* eof */
#endif
