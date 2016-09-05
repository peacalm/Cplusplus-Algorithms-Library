/*
 * string-extended header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-5-10
 */

#ifndef __STRING_EXTENDED_H__
#define __STRING_EXTENDED_H__

#include <string>
#include <vector>
#include <stack>



// calculator of string s formed by "0123456789+-*/()" and white space.
inline int calculator(std::string s) {
	s += '+';
	int n = int(s.size());
	int ret = 0;
	int last = 1;
	char op = '*';
	std::stack<int> stk;
	int num = 0;
	for (int i = 0; i < n; ++i) {
		char c = s[i];
		if (isdigit(c)) {
			num = num * 10 + c - '0';
			continue;
		}
		if (isspace(c)) continue;
		if (c == '+' || c == '-') {
			ret += op == '*' ? last * num : last / num;
			last = c == '+' ? 1 : -1;
			op = '*';
		}
		else if (c == '*' || c == '/') {
			last = op == '*' ? last * num : last / num;
			op = c;
		}
		else if (c == '(') {
			stk.push(op);
			stk.push(last);
			stk.push(ret);
			ret = 0;
			last = 1;
			op = '*';
		}
		else if (c == ')') {
			num = ret + (op == '*' ? last * num : last / num);
			ret = stk.top(); stk.pop();
			last = stk.top(); stk.pop();
			op = stk.top(); stk.pop();
			continue;
		}
		num = 0;
	}
	return ret;
}

// if all chars of s are English characters, or in a-z or A-Z.
inline bool isalpha(const std::string& s) {
	for (size_t i = 0; i < s.size(); ++i)
		if (!(
			(s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')
			)) return false;
	return true;
}

// if all chars of s are decimal digit character, or in 0-9.
inline bool isdigit(const std::string& s) {
	for (size_t i = 0; i < s.size(); ++i)
		if (s[i] < '0' || s[i] > '9') return false;
	return true;
}

// if all chars of s are lowercase English characters, or in a-z.
inline bool islower(const std::string& s) {
	for (size_t i = 0; i < s.size(); ++i)
		if (s[i] < 'a' || s[i] > 'z') return false;
	return true;
}

// if all chars of s are uppercase English characters, or in A-Z.
inline bool isupper(const std::string& s) {
	for (size_t i = 0; i < s.size(); ++i)
		if (s[i] < 'A' || s[i] > 'Z') return false;
	return true;
}

// convert lowercase letters in s to uppercase.
inline std::string& to_upper(std::string& s) {
	for (size_t i = 0; i < s.size(); ++i) {
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] = 'A' + (s[i] - 'a');
	}
	return s;
}

// convert uppercase letters in s to lowercase.
inline std::string& to_lower(std::string& s) {
	for (size_t i = 0; i < s.size(); ++i) {
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] = 'a' + (s[i] - 'A');
	}
	return s;
}

// remove the leading and tailing chars equal to delim.
inline std::string& strip(std::string& s, const char delim = ' ') {
	while (s.size() && s.back() == delim) s.pop_back();
	while (s.size() && s.front() == delim) s.erase(s.begin());
	return s;
}

// split string s by one delimit char
inline std::vector<std::string> split(const std::string& s, const char delim = ' ') {
	std::vector<std::string> ret;
	int n = int(s.size());
	int b = 0;
	while (b < n && s[b] == delim) ++b;
	for (int i = b; i < n; ++i) {
		if (s[i] == delim) {
			ret.push_back(s.substr(b, i - b));
			while (i + 1 < n && s[i + 1] == delim) ++i;
			b = i + 1;
			continue;
		}
		if (i == n - 1) ret.push_back(s.substr(b));
	}
	return ret;
}

// split string s by many delimit chars formed in a C-style char array.
inline std::vector<std::string> split(const std::string& s, const char* delims) {
	std::vector<bool> isdelim(128, false);
	while (*delims) isdelim[int(*delims++)] = true;

	std::vector<std::string> ret;
	int n = int(s.size());
	int b = 0;
	while (b < n && isdelim[s[b]]) ++b;
	for (int i = b; i < n; ++i) {
		if (isdelim[s[i]]) {
			ret.push_back(s.substr(b, i - b));
			while (i + 1 < n && isdelim[s[i + 1]]) ++i;
			b = i + 1;
			continue;
		}
		if (i == n - 1) ret.push_back(s.substr(b));
	}
	return ret;
}

// split string s by many delimit chars formed in string.
inline std::vector<std::string> split(const std::string& s, const std::string& delims) {
	return split(s, delims.c_str());
}


/* eof */
#endif
