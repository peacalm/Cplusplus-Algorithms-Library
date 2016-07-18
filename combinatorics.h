/*
 * combinatorics header
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-7-10
 * last edit on 2016-7-16
 */

#ifndef	__COMBINATORICS_H__
#define __COMBINATORICS_H__

#include <vector>


//  permutations of 1,2,...,N-1
//  permutation id is 0,1,2,...,(N!-1)

// function to calc i!
inline long long fact(int i) {
	static std::vector<long long> dp;
	if (dp.size() > i) return dp[i];
	if (dp.empty()) dp.push_back(1);
	while (dp.size() <= i) dp.push_back(dp.back() * dp.size());
	return dp[i];
}
// to calc permutation id of a permutation of 1,2,...,N
inline long long Cantor(const std::vector<int>& a) {
	long long ret = 0;
	for (int i = 0; i < a.size(); ++i) {
		int tp = 0;
		for (int j = i + 1; j < a.size(); ++j)
			if (a[j] < a[i]) ++tp;
		ret += tp * fact(a.size() - i - 1);
	}
	return ret;
}
// to calc a permutation of 1,2,...,N whose permutation id is id
inline std::vector<int> unCantor(int N, long long id) {
	std::vector<int> ret(N);
	std::vector<bool> used(N + 1, false);
	for (int i = 1; i < N + 1; ++i) {
		long long a = id / fact(N - i);
		id %= fact(N - i);
		int cnt = 0;
		for (int j = 1; j < N + 1; ++j) if (!used[j]) {
			if (++cnt == a + 1) {
				ret[i - 1] = j;
				used[j] = true;
				break;
			}
		}
	}
	return ret;
}


/* eof */
#endif