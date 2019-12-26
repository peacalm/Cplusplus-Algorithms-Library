/*
 * output-extended header
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-5-10
 */

#ifndef __OUTPUT_EXTENDED_H__
#define __OUTPUT_EXTENDED_H__
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <initializer_list>
#include <utility>


// translate an IntegerType to binary string
// split each `group_size` chars with a `delim`
template<typename IntegerType> std::string to_binary(IntegerType a, int group_size = 0, char delim = ' ') {
	std::string ret;
	for (int i = sizeof(IntegerType) * 8 - 1; i >= 0; --i) {
		ret += a & (1LL << i) ? '1' : '0';
		if (group_size != 0 && i % group_size == 0) ret += delim;
	}
	return ret;
}

// overload operator<< for std::pair and all containters

//////////////////// declarations ////////////////////

// std::pair
template<typename T, typename U> 
std::ostream& operator<< (std::ostream& os, const std::pair<T, U>& p);

// array_printer
template<typename T>
std::ostream& array_printer(std::ostream& os, const T* a, const size_t n,
							const char* delim = " ", const char* leftbound = "", const char* rightbound = "");

// container_printer
template<typename Container>
std::ostream& container_printer(std::ostream& os, const Container& c,
								const char* delim = " ", const char* leftbound = "", const char* rightbound = "");

// std::array
template<typename T, size_t N>
std::ostream& operator << (std::ostream& os, const std::array<T, N>& a);

// std::deque
template<typename T>
std::ostream& operator << (std::ostream& os, const std::deque<T>& d);

// std::forward_list
template<typename T>
std::ostream& operator << (std::ostream& os, const std::forward_list<T>& f);

// std::list
template<typename T>
std::ostream& operator << (std::ostream& os, const std::list<T>& l);

// std::set
template<typename T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s);

// std::multiset
template<typename T>
std::ostream& operator << (std::ostream& os, const std::multiset<T>& s);

// std::unordered_set
template<typename T>
std::ostream& operator << (std::ostream& os, const std::unordered_set<T>& s);

// std::vector
template<typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v);

// std::initializer_list
template<typename T>
std::ostream& operator << (std::ostream &os, const std::initializer_list<T>& il);

// std::map
template<typename T, typename U>
std::ostream& operator << (std::ostream& os, const std::map<T, U>& m);

// std::multimap
template<typename T, typename U>
std::ostream& operator << (std::ostream& os, const std::multimap<T, U>& m);

// std::unordered_map
template<typename T, typename U>
std::ostream& operator << (std::ostream& os, const std::unordered_map<T, U>& m);


//////////////////// implementations ////////////////////

template<typename T, typename U>
std::ostream& operator<< (std::ostream& os, const std::pair<T, U>& p) {
	os << "(" << p.first << ", " << p.second << ")" << std::flush;
	return os;
}

template<typename T>
std::ostream& array_printer(std::ostream& os, const T* a, const size_t n,
							const char* delim, const char* leftbound, const char* rightbound) {
	os << leftbound;
	if (n) {
		os << a[0];
		for (size_t i = 1; i < n; ++i) os << delim << a[i];
	}
	os << rightbound;
	return os << std::flush;
}

template<typename Container>
std::ostream& container_printer(std::ostream& os, const Container& c,
								const char* delim, const char* leftbound, const char* rightbound) {
	auto b = c.begin(), e = c.end();
	os << leftbound;
	if (b != e) {
		os << *b++;
		for (; b != e; ++b) os << delim << *b;
	}
	os << rightbound;
	return os << std::flush;
}

template<typename T, size_t N>
std::ostream& operator << (std::ostream& os, const std::array<T, N>& a) {
	return container_printer(os, a, " ", "[ ", " ]");
}

template<typename T>
std::ostream& operator << (std::ostream& os, const std::deque<T>& d) {
	return container_printer(os, d, " ", "[ ", " ]");
}

template<typename T>
std::ostream& operator << (std::ostream& os, const std::forward_list<T>& f) {
	return container_printer(os, f, " ", "[ ", " ]");
}

template<typename T>
std::ostream& operator << (std::ostream& os, const std::list<T>& l) {
	return container_printer(os, l, " ", "[ ", " ]");
}

template<typename T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s) {
	return container_printer(os, s, " ", "{ ", " }");
}

template<typename T>
std::ostream& operator << (std::ostream& os, const std::multiset<T>& s) {
	return container_printer(os, s, " ", "{ ", " }");
}

template<typename T>
std::ostream& operator << (std::ostream& os, const std::unordered_set<T>& s) {
	return container_printer(os, s, " ", "{ ", " }");
}

template<typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v) {
	return container_printer(os, v, " ", "[ ", " ]");
}

template<typename T>
std::ostream& operator << (std::ostream &os, const std::initializer_list<T>& il) {
	return container_printer(os, il, " ", "{ ", " }");
}

template<typename T, typename U>
std::ostream& operator << (std::ostream& os, const std::map<T, U>& m) {
	typename std::map<T, U>::const_iterator b = m.cbegin(), e = m.cend();
	os << "{";
	for (; b != e; ++b) os << " " << b->first << ":" << b->second;
	os << " }" << std::flush;
	return os;
}

template<typename T, typename U>
std::ostream& operator << (std::ostream& os, const std::unordered_map<T, U>& m) {
	typename std::unordered_map<T, U>::const_iterator b = m.cbegin(), e = m.cend();
	os << "{";
	for (; b != e; ++b) os << " " << b->first << ":" << b->second;
	os << " }" << std::flush;
	return os;
}

template<typename T, typename U>
std::ostream& operator << (std::ostream& os, const std::multimap<T, U>& m) {
	typename std::multimap<T, U>::const_iterator b = m.cbegin(), e = m.cend();
	os << "{";
	for (; b != e; ++b) os << " " << b->first << ":" << b->second;
	os << " }" << std::flush;
	return os;
}

/* eof */
#endif