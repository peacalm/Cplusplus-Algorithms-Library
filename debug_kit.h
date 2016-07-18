/*
 * debug-kit header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-5-10
 */
// NOTE: this is C++11 demanded
#ifndef __DEBUG_KIT_H__
#define __DEBUG_KIT_H__

#include "cil_config.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include "string_extended.h"
using std::string;
using std::vector;
using std::cout;

inline string to_string(const string &a) { return a; }
inline string to_string(const char *a) { return string(a); }
template<typename T> inline string to_string(const T &t) {
	ostringstream os;
	os << t;
	return os.str();
}



#ifdef __cpp11

// get the variables' name strings in vector
template <typename A>
inline void variable_value_to_string(vector<string> &values, const A &a) {
	values.push_back(to_string(a));
}
template <typename A, typename... Args>
inline void variable_value_to_string(vector<string> &values, const A &a, const Args&... rest) {
	values.push_back(to_string(a));
	variable_value_to_string(values, rest...);
}

// get the variable names and values in string, then output in pair like "key = value"
#define watch(...) {\
	vector<string> values;\
	variable_value_to_string(values, __VA_ARGS__);\
	string var_names = string(#__VA_ARGS__);\
	vector<string> keys = split(var_names, ',');\
	for (int i = 0; i < values.size(); ++i) {\
		cout << strip(keys[i]) << " = " << values[i] << endl;\
	}\
	cout << endl;\
}

#else

#define watch /\
/

#endif

/* eof */
#endif