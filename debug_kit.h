/*
 * debug-kit header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-5-10
 * last edit on 2016-9-5 add __split_for_watch instead of split and strip in string_extended.h
 */

// NOTE: this is C++11 required

#ifndef __DEBUG_KIT_H__
#define __DEBUG_KIT_H__

#include "cil_config.h"
#include "output_extended.h"

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>


// convert all types of variables into string.
inline std::string to_string(const std::string& a) { return a; }
inline std::string to_string(const char* a) { return std::string(a); }
template<typename T> inline std::string to_string(const T& t) {
	std::ostringstream os;
	os << t;
	return os.str();
}


#ifdef __cpp11

// split string s by ',' out of parenthesis, and remove white spaces of splited string.
inline std::vector<std::string> __split_for_watch(const std::string& s) {
	std::vector<std::string> ret;
	std::string subs;
	int n = int(s.size());
	int i = 0;
	while (i < n && (s[i] == ',' || s[i] == ' ')) ++i;
	for (; i < n; ++i) {
		if (s[i] == ' ') continue;
		if (s[i] == '(') {
			int sum = -1;
			subs += s[i];
			while (sum) {
				++i;
				subs += s[i];
				if (s[i] == '(') --sum;
				if (s[i] == ')') ++sum;
			}
			continue;
		}
		if (s[i] == '<') {
			int sum = -1;
			subs += s[i];
			while (sum) {
				++i;
				subs += s[i];
				if (s[i] == '<') --sum;
				if (s[i] == '>') ++sum;
			}
			continue;
		}
		if (s[i] == ',') {
			ret.push_back(subs);
			subs.clear();
			while (i + 1 < n && (s[i + 1] == ',' || s[i + 1] == ' ')) ++i;
			continue;
		}
		subs += s[i];
	}
	if (subs.size()) {
		ret.push_back(subs);
		subs.clear();
	}
	return ret;
}

// get the variables' name strings in vector
template <typename A>
inline void variable_value_to_string(std::vector<std::string>& values, const A& a) {
	values.push_back(to_string(a));
}
template <typename A, typename... Args>
inline void variable_value_to_string(std::vector<std::string>& values, const A& a, const Args&... rest) {
	values.push_back(to_string(a));
	variable_value_to_string(values, rest...);
}

// get the variable names and values in string, then output in pair like "key = value"
#define watch(...) {\
	std::vector<std::string> values;\
	variable_value_to_string(values, __VA_ARGS__);\
	std::string var_names = std::string(#__VA_ARGS__);\
	std::vector<std::string> keys = __split_for_watch(var_names);\
	for (size_t i = 0; i < values.size(); ++i) {\
		std::cout << keys[i] << " = " << values[i] << std::endl;\
	}\
	std::cout << std::endl;\
}


#else

// define watch as nothing if no cplusplus-11 support.
#define watch /\
/

#endif

/* eof */
#endif
