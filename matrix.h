/*
 * matrix header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-4-18
 * last edit on: 2016-5-30: add template matrix edition
 */

#ifndef __MATRIX_H__
#define __MATRIX_H__

#if ((defined(__cplusplus) && (__cplusplus >= 201103L) || defined(_MSC_VER) && (_MSC_VER >= 1900)))
#define __cpp11
#endif
#include <cassert>
#include <cstring>
#include <string>
#include <initializer_list>
#include <iostream>


 /* ******************************************************
 f[0] = 0;
 f[1] = 1;
 f[2] = 1;
 f[3] = 2;
 f[4] = 3;
 ......
 f[n] = f[n-1] + f[n-2]

 matrix<2> fabonacci{ 0, 1, 1, 1 };

 fabonacci = { 0 1 }  =  { f[0] f[1] }
 fabonacci = { 1 1 }  =  { f[1] f[2] }

 (fabonacci)^n = { f[n-1] f[n]   }
 (fabonacci)^n = { f[n]   f[n+1] }
 ****************************************************** */

template<int N> class matrix {
	long long a[N][N];
public:
	matrix() { memset(a, 0, sizeof(a)); }
	matrix(int u) {
		memset(a, 0, sizeof(a));
		for (int i = 0; i < N; ++i) a[i][i] = u;
	}
	matrix(long long u) {
		memset(a, 0, sizeof(a));
		for (int i = 0; i < N; ++i) a[i][i] = u;
	}
	matrix(const matrix& B) {
		memcpy(a, B.a, sizeof(a));
	}
#ifdef __cpp11
	matrix(std::initializer_list<long long> il) {
		assert(il.size() <= N * N);
		int cnt = 0;
		for (std::initializer_list<long long>::iterator it = il.begin(), e = il.end(); it != e; ++it) {
			a[cnt / N][cnt % N] = *it;
			++cnt;
		}
	}
#endif
	~matrix() {}
	void clear() { memset(a, 0, sizeof(a)); }
	void unitize() {
		memset(a, 0, sizeof(a));
		for (int i = 0; i < N; ++i) a[i][i] = 1;
	}
	long long* operator [] (int r) { return a[r]; }
	const long long* operator [] (int r) const { return a[r]; }
	matrix operator *(const matrix& B) const {
		matrix ret;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				for (int k = 0; k < N; ++k)
					ret[i][j] += a[i][k] * B[k][j];
		return ret;
	}
	matrix& operator *= (const matrix& B) { return *this = (*this) * B; }
	matrix pow(long long n) const {
		matrix ret(1), x(*this);
		while (n) {
			if (n & 1) ret *= x;
			x *= x;
			n >>= 1;
		}
		return ret;
	}
	matrix mmul(const matrix& B, long long mod) const {
		matrix ret;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				for (int k = 0; k < N; ++k)
					ret[i][j] = (ret[i][j] + a[i][k] * B[k][j] % mod) % mod;
		return ret;
	}
	matrix mpow(long long n, long long mod) const {
		matrix ret(1), x(*this);
		while (n) {
			if (n & 1) ret = ret.mmul(x, mod);
			x = x.mmul(x, mod);
			n >>= 1;
		}
		return ret;
	}
};

template<int N>
inline std::ostream& operator <<(std::ostream& os, const matrix<N>& A) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N - 1; ++j) os << A[i][j] << " ";
		os << A[i][N - 1] << "\n";
	}
	return os;
}

template<int N>
inline matrix<N> mmul(const matrix<N>& A, const matrix<N>& B, long long mod) {
	matrix<N> ret;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k)
				ret[i][j] = (ret[i][j] + A[i][k] * B[k][j] % mod) % mod;
	return ret;
}

template<int N>
inline matrix<N> mpow(const matrix<N>& A, long long n, long long mod) {
	matrix<N> ret(1), x(A);
	while (n) {
		if (n & 1) ret = mmul(ret, x, mod);
		x = mmul(x, x, mod);
		n >>= 1;
	}
	return ret;
}



#if 0
// old edition, should rewrite N value each time used.
class Matrix {
public:
	static const int N = 2;
	long long a[N][N];
	Matrix();
	Matrix(int u);
	Matrix(const Matrix& B);
	void clear();
	void unitize();
	long long* operator [] (int r);
	const long long* operator [] (int r) const;
	Matrix operator *(const Matrix& B) const;
	Matrix& operator *= (const Matrix& B);
	Matrix pow(long long n) const;
	Matrix mpow(long long n, long long mod) const;
	friend Matrix mmul(const Matrix& A, const Matrix& B, long long mod);
	friend ostream& operator <<(ostream& os, const Matrix& A);
};
Matrix::Matrix() {
	memset(a, 0, sizeof(a));
}
Matrix::Matrix(int u) {
	memset(a, 0, sizeof(a));
	for (int i = 0; i < N; ++i) a[i][i] = u;
}
Matrix::Matrix(const Matrix& B) {
	memcpy(a, B.a, sizeof(B.a));
}
void Matrix::clear() {
	memset(a, 0, sizeof(a));
}
void Matrix::unitize() {
	memset(a, 0, sizeof(a));
	for (int i = 0; i < N; ++i) a[i][i] = 1;
}
long long* Matrix::operator [] (int r) {
	return a[r];
}
const long long* Matrix::operator [] (int r) const {
	return a[r];
}
Matrix Matrix::operator *(const Matrix& B) const {
	Matrix ret;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k) {
				ret.a[i][j] += a[i][k] * B.a[k][j];
			}
	return ret;
}
Matrix& Matrix::operator *= (const Matrix& B) {
	return *this = (*this) * B;
}
Matrix Matrix::pow(long long n) const {
	Matrix ret(1), a(*this);
	while (n) {
		if (n & 1) ret *= a;
		a *= a;
		n >>= 1;
	}
	return ret;
}
Matrix Matrix::mpow(long long n, long long mod) const {
	Matrix ret(1), a(*this);
	while (n) {
		if (n & 1) ret = mmul(ret, a, mod);
		a = mmul(a, a, mod);
		n >>= 1;
	}
	return ret;
}
inline Matrix mmul(const Matrix& A, const Matrix& B, long long mod) {
	const int& N = A.N;
	Matrix ret;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			for (int k = 0; k < N; ++k) {
				ret.a[i][j] = (ret.a[i][j] + A.a[i][k] * B.a[k][j] % mod) % mod;
			}
	return ret;
}
inline ostream& operator <<(ostream& os, const Matrix& A) {
	for (int i = 0; i < A.N; ++i) {
		for (int j = 0; j < A.N - 1; ++j)
			os << A.a[i][j] << " ";
		os << A.a[i][A.N - 1] << "\n";
	}
	return os;
}
#endif








#if 0
/**
 *	square matrix formed in template.
 *	T could be int, long long, double, etc.
 *	N > 0, denotes dimension of the matrix.
 */
template<typename T, int N>
class matrix {
public:
	T a[N][N];
	matrix() {
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				a[i][j] = 0;
	}
	matrix(T u) {
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				a[i][j] = i == j ? u : 0;
	}
	matrix(const matrix& B) {
		memcpy(a, B.a, sizeof(B.a));
	}
	void clear() {
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				a[i][j] = 0;
	}
	void unitize() {
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				a[i][j] = i == j ? 1 : 0;
	}
	matrix operator *(const matrix& B) const {
		matrix ret;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				for (int k = 0; k < N; ++k) {
					ret.a[i][j] += a[i][k] * B.a[k][j];
				}
		return ret;
	}
	matrix& operator *= (const matrix& B) {
		return *this = (*this) * B;
	}
	//friend matrix mmul(const matrix& A, const matrix& B, int mod);
};

#endif

/* eof */
#endif