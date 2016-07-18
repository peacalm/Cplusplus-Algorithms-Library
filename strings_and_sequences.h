/*
 * strings-and-sequences header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-5-10
 */

#ifndef __STRINGS_AND_SEQUENCES_H__
#define __STRINGS_AND_SEQUENCES_H__
#include <string>
#include <vector>
#include <algorithm>


//// find the max xor result of two integer in a array
//namespace max_xor {
//
//	const int MAX_BIT = 31;
//	int trie[1000001][2], cnt;
//	void init() {
//		memset(trie, 0, sizeof(trie));
//		cnt = 0;
//	}
//	void insert(int u) {
//		int head = 0;
//		for (int i = MAX_BIT - 1; i >= 0; --i) {
//			int t = (u >> i) & 1;
//			if (trie[head][t]) head = trie[head][t];
//			else head = trie[head][t] = ++cnt;
//		}
//	}
//	int query_max(int u, int head = 0, int dep = 0) {
//		if (dep >= MAX_BIT) return 0;
//		int offset = (MAX_BIT - 1 - dep);
//		int t = u >> offset & 1;
//		if (trie[head][t ^ 1])
//			return 1 << offset | query_max(u, trie[head][t ^ 1], dep + 1);
//		else
//			return query_max(u, trie[head][t], dep + 1);
//	}
//	int solve_max_xor(const std::vector<int> &a) {
//		init();
//		int ret = -1;
//		for (int i = 0; i < a.size(); ++i) {
//			insert(a[i]);
//			ret = std::max(ret, query_max(a[i]));
//		}
//		return ret;
//	}
//
//} //using namespace max_xor;

// find the max xor result of two integer in a array
// for long long type -_-|||
//namespace max_xor_LL {
//
//	const int MAX_BIT = 40;
//	long long trie[__][2], cnt;
//	void init() {
//		memset(trie, 0, sizeof(trie));
//		cnt = 0;
//	}
//	void insert(long long u) {
//		int head = 0;
//		for (int i = MAX_BIT - 1; i >= 0; --i) {
//			int t = (u >> i) & 1LL;
//			if (trie[head][t]) head = trie[head][t];
//			else head = trie[head][t] = ++cnt;
//		}
//	}
//	long long query_max(long long u, int head = 0, int dep = 0) {
//		if (dep >= MAX_BIT) return 0;
//		int offset = (MAX_BIT - 1 - dep);
//		int t = u >> offset & 1LL;
//		if (trie[head][t ^ 1])
//			return 1LL << offset | query_max(u, trie[head][t ^ 1], dep + 1);
//		else
//			return query_max(u, trie[head][t], dep + 1);
//	}
//	long long solve_max_xor(const vector<long long> &a) {
//		init();
//		long long ret = -1;
//		for (int i = 0; i < a.size(); ++i) {
//			insert(a[i]);
//			ret = max(ret, query_max(a[i]));
//		}
//		return ret;
//	}
//
//} //using namespace max_xor_LL;


// C style KMP implement, calculate pattern's occurrence times in text
inline void calc_KMP_next(const char pattern[], int n, int next[]) {
	next[0] = -1;
	for (int i = 0, j = -1; i < n;) {
		while (j >= 0 && pattern[i] != pattern[j]) j = next[j];
		++i; ++j;
		next[i] = pattern[i] == pattern[j] ? next[j] : j;
	}
}
inline int KMP_count_occurrence(const char text[], int n, const char pattern[], int m) {
	int *next = new int[m + 1];
	calc_KMP_next(pattern, m, next);
	int cnt = 0;
	for (int i = 0, j = 0; i < n; ++i) {
		while (j >= 0 && text[i] != pattern[j]) j = next[j];
		if (++j >= m) { ++cnt; j = next[j]; }
	}
	delete[] next;
	return cnt;
}
inline int KMP_count_occurrence(const char text[], const char pattern[]) {
	return KMP_count_occurrence(text, strlen(text), pattern, strlen(pattern));
}

// C++ style KMP implement, calculate pattern's occurrence times in text
inline std::vector<int> calc_KMP_next(const std::string& pattern) {
	int n = pattern.size();
	std::vector<int> next(n + 1, -1);
	for (int i = 0, j = -1; i < n;) {
		while (j >= 0 && pattern[i] != pattern[j]) j = next[j];
		++i; ++j;
		next[i] = pattern[i] == pattern[j] ? next[j] : j;
	}
	return next;
}
inline int KMP_count_occurrence(const std::string& text, const std::string& pattern) {
	int n = text.size(), m = pattern.size();
	std::vector<int> next = calc_KMP_next(pattern);
	int cnt = 0;
	for (int i = 0, j = 0; i < n; ++i) {
		while (j >= 0 && text[i] != pattern[j]) j = next[j];
		if (++j >= m) { ++cnt; j = next[j]; }
	}
	return cnt;
}


// longest palindromic subsequence
inline int LPS(const std::string& s) {
	int n = s.size();
	std::vector<std::vector<int> > dp(n, std::vector<int>(n, 0));
	for (int r = 0; r < n; ++r) {
		dp[r][r] = 1;
		for (int l = r - 1; l >= 0; --l) {
			if (s[l] == s[r]) dp[l][r] = 2 + dp[l + 1][r - 1];
			else dp[l][r] = std::max(dp[l + 1][r], dp[l][r - 1]);
		}
	}
	return dp[0][n - 1];
}

// return length of the longest palindrome substring
// pass original string s, and it's length n, and two extra array space not shorter than 2*n+3
// es is extended string inserted '#' in s,
// r represents the palindrom's radius, where one-character-palindrome's r is 1.
inline int Manacher(char s[], int n, char es[], int r[]) {
	int cnt = 0;
	es[cnt++] = -1;
	es[cnt++] = '#';
	for (int i = 0; i < n; ++i) {
		es[cnt++] = s[i];
		es[cnt++] = '#';
	}
	es[cnt] = 0;
	int mx = 0, id = 0;
	for (int i = 1; i < cnt; ++i) {
		r[i] = mx > i ? std::min(r[id * 2 - i], mx - i) : 1;
		while (es[i - r[i]] == es[i + r[i]]) ++r[i];
		if (i + r[i] > mx) {
			mx = i + r[i];
			id = i;
		}
	}
	int ret = 1;
	for (int i = 1; i < cnt; ++i) ret = std::max(ret, r[i] - 1);
	return ret;
}

// longest common sequences
inline int LCS(const std::string& a, const std::string& b) {
	int n = a.size();
	int m = b.size();
	std::vector<std::vector<int> > dp(n + 1, std::vector<int>(m + 1));
	for (int i = 1; i < n + 1; ++i) {
		for (int j = 1; j < m + 1; ++j) {
			if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	return dp[n][m];
}
template<typename T> inline int LCS(const std::vector<T>& a, const std::vector<T>& b) {
	int n = a.size();
	int m = b.size();
	std::vector<std::vector<int> > dp(n + 1, std::vector<int>(m + 1));
	for (int i = 1; i < n + 1; ++i) {
		for (int j = 1; j < m + 1; ++j) {
			if (a[i - 1] == b[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	return dp[n][m];
}

// edit distance
inline int edit_distance(const std::string& a, const std::string& b) {
	int n = a.size();
	int m = b.size();
	std::vector<std::vector<int> > dp(n + 1, std::vector<int>(m + 1));
	for (int i = 0; i < n + 1; ++i) dp[i][0] = i;
	for (int j = 0; j < m + 1; ++j) dp[0][j] = j;
	for (int i = 1; i < n + 1; ++i) {
		for (int j = 1; j < m + 1; ++j) {
			int t = a[i - 1] == b[j - 1] ? 0 : 1;
			int x = dp[i - 1][j - 1] + t;
			int y = std::min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
			dp[i][j] = std::min(x, y);
		}
	}
	return dp[n][m];
}


// longest increasing sequences
inline int LIS(const std::vector<int>& a) {
	int n = a.size();
	std::vector<int> v;
	for (int i = 0; i < n; ++i) {
		std::vector<int>::iterator it = upper_bound(v.begin(), v.end(), a[i]);
		if (it == v.end()) v.push_back(a[i]);
		else *it = a[i];
	}
	return v.size();
}
inline int strictly_LIS(const std::vector<int>& a) {
	int n = a.size();
	std::vector<int> v;
	for (int i = 0; i < n; ++i) {
		std::vector<int>::iterator it = lower_bound(v.begin(), v.end(), a[i]);
		if (it == v.end()) v.push_back(a[i]);
		else *it = a[i];
	}
	return v.size();
}
// the minimum modificatin to make the sequence srictly increasing
// each time of modification can change a number into any value
inline int min_modification_to_strictly_increasing(const std::vector<int>& a) {
	int n = a.size();
	std::vector<int> v;
	for (int i = 0; i < n; ++i) {
		int t = a[i] - i;
		std::vector<int>::iterator it = upper_bound(v.begin(), v.end(), t);
		if (it == v.end()) v.push_back(t);
		else *it = t;
	}
	return n - int(v.size());
}




/* eof */
#endif