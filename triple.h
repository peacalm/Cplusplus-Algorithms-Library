/*
 * triple header
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-3-29
 */

#ifndef __TRIPLE_H__
#define __TRIPLE_H__

template<typename T, typename U, typename V> class triple {
public:
	T first;
	U second;
	V third;
	triple() {};
	triple(const T&a, const U&b, const V&c) : first(a), second(b), third(c) {}
	~triple() {}
	triple & operator = (const triple&b) { 
		first = b.first;
		second = b.second;
		third = b.third;
		return *this;
	}
	bool operator == (const triple &b) const {
		return first == b.first && second == b.second && third == b.third;
	}
	bool operator < (const triple &b) const { 
		return first != b.first ? first < b.first : (second != b.second ? second < b.second : third < b.third);
	}
	bool operator > (const triple &b) const {
		return first != b.first ? first > b.first : (second != b.second ? second > b.second : third > b.third);
	}
	bool operator <= (const triple &b) const {
		return *this < b || *this == b;
	}
	bool operator >= (const triple &b) const {
		return *this > b || *this == b;
	}
};
template<typename T, typename U, typename V> triple<T, U, V> make_triple(const T&a, const U&b, const V&c) { return triple<T, U, V>(a, b, c); }

#define mt  make_triple
typedef triple<int, int, int> TIII;
typedef triple<long long, long long, long long> TLLL;
typedef vector<TIII> VTIII;
typedef vector<TLLL> VTLLL;

/* eof */
#endif