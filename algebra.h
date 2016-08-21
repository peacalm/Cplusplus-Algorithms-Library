/*
 * algebra header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-8-21
 */

#ifndef __ALGEBRA_H__
#define __ALGEBRA_H__

#include <iostream>
#include <vector>
#include <utility>


inline std::vector<double> Gauss(std::vector<std::vector<double>>& a, std::vector<double>& b, const double eps = 1e-9) {
	int n = a.size();
	int m = a[0].size();
	std::vector<double> ret(m);
	for (int c = 0; c < m; ++c) {
		bool find_nonzero = false;
		for (int r = c; r < n; ++c) if (a[r][c] != 0) {
			find_nonzero = true;
			std::swap(a[r], a[c]);
			break;
		}
		if (!find_nonzero) {
			std::cerr << "Many Solutions!" << std::endl;
			return ret;
		}
		for (int r = 0; r < n; ++r) if (r != c) {
			double k = a[r][c] / a[c][c];
			for (int cc = 0; cc < m; ++cc) a[r][cc] -= a[c][cc] * k;
			b[r] -= b[c] * k;
		}
	}
	for (int r = 0; r < n; ++r) {
		bool find_nonzero = false;
		for (int c = 0; c < m; ++c) if (a[r][c] != 0) {
			find_nonzero = true;
			break;
		}
		if (!find_nonzero && abs(b[r]) > eps) {
			std::cerr << "No Solutions!" << std::endl;
			return ret;
		}
	}
	for (int i = 0; i < m; ++i) ret[i] = b[i] / a[i][i];
	return ret;
}

 /* eof */
#endif