/*
 * number theory header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2015-12-16
 * last edit on 2016-7-15
 */

#ifndef __NUMBER_THEORY_H__
#define __NUMBER_THEORY_H__

#include "cil_config.h"
#include <cstring>
#include <cmath>
#include <vector>
#include <stack>
#include <algorithm>
#include <bitset>

// /* **************************************************************************
//// FUNCTION PROTOTYPES STSRT

// gcd, greatest common divisor
template<typename T> T gcd(T a, T b);
#ifdef __cpp11
template<typename T, typename ...Args> T gcd(T a, T b, Args... rest);
#endif

// lcm, lowest common multiple
template<typename T> T lcm(T a, T b);
#ifdef __cpp11
template<typename T, typename ...Args> T lcm(T a, T b, Args... rest);
#endif

// extend gcd
template<typename T> T egcd(T a, T b, T& x, T& y);



//// 4 kinds of method to get modular multiplicative inverse

// modular multiplicative inverse using extend gcd, a and mod must be coprime.
template<typename T, typename U> T minv(T a, const U mod);
// another short modular multiplicative inverse
// mod must be prime.
// if mod is too big, like 1e18+9 for long long type, this may overflow and get wrong answer.
template <typename T, typename U> T minv_brief(T a, U mod);
// modular multiplicative inverse using power(a, mod - 2, mod), mod must be prime.
// if mod is too big, like 1e18+9 for long long type, this may overflow and get wrong answer.
template<typename T, typename U> T minv_power(T a, U mod);
// modular multiplicative inverse using power(a, phi(mod) - 1, mod), (a, mod) = 1.
// if mod is too big, like 1e18+9 for long long type, this may overflow and get wrong answer.
template<typename T, typename U> T minv_power_phi(T a, U mod);


// Euler's phi function, or Euler's totient function
template<typename T> T phi(T n);

// quick power
template<typename T, typename U> T power(T x, U n);
template<typename T, typename U, typename V> T power(T x, U n, V mod);
template<typename T, typename V> T power(T x, int n, V mod);
template<typename T, typename V> T power(T x, unsigned int n, V mod);
template<typename T, typename V> T power(T x, long long n, V mod);
template<typename T, typename V> T power(T x, unsigned long long n, V mod);

// advanced modulo-multiply for positive integer by bits, to avoid overflow
template<typename T, typename U, typename V> T bitmmul(T a, U b, V mod);
// advanced quick-modulo-power for positive integer by bits, to avoid overflow
template<typename T, typename U, typename V> T bitmpow(T a, U n, V mod);

// miller-Rabin primality test
bool Miller_Rabin(unsigned int n);
bool Miller_Rabin(int n);
bool Miller_Rabin(unsigned long long n);
bool Miller_Rabin(long long n);

// modular multiplicative inverse of a consecutive integers 1,2,3,...,n-1 modulo mod
// mod must be prime
void get_minv_array(int minv[], int n, const int mod);


// sieve of Euler to get primes less than n, O(n)
void get_primes(int n, std::vector<int>& primes, std::vector<bool>& is_prime);
void get_primes(int n, std::vector<int>& primes);
std::vector<int> get_primes(int n);

// calculate phi for integer 1, 2, 3, ... , n-1.
void get_phi_array(int n, std::vector<bool>& is_prime, std::vector<int>& primes, std::vector<int>& phi);
std::vector<int> get_phi_array(int n);

// sieve of Euler to get all prime numbers less than N
// as well as to judge if a number less than N is prime
template<int N> class sieve_of_Euler;
//public member functions
//	static void init();
//	static const bitset<N>& is_prime();
//	static const std::vector<int>& primes();
//	static bool is_prime(int i);
//	static int primes(int i);

template<int MAX_FACT, int mod>
class factorial_and_combination;
//public member functions
//	static void init();
//	static int fact(int i);
//	static int inv_fact(int i);
//	static int C(int n, int m);

/// Yanghui triangle
//template<int n, typename T = int, int mod = -1>
//class Yanghui_triangle;
/// specialized without modulo
//template<int n, typename T> class Yanghui_triangle<n, T, -1>;
//public member functions
//	Yanghui_triangle();
//	void display();
//	T C(int i, int j);

// Josephus problem. 
// n people(0,1, ..., n-1) form a circle, start from 0, skip out one every k people.
// repeat n-1 times, calculate id of last one remained.
int Josephus(int n, int k);


//// FUNCTION PROTOTYPES END
// ************************************************************************** */




// gcd, greatest common divisor
#if 1
// iterative edition
template<typename T>
inline T gcd(T a, T b) {
	while (b != 0) {
		T tmp = b;
		b = a % b;
		a = tmp;
	}
	return a;
}
#else
// brief recursive edition
template<typename T> inline T gcd(T a, T b) { return b ? gcd(b, a % b) : a; }
#endif

#ifdef __cpp11
template<typename T, typename ...Args>
inline T gcd(T a, T b, Args... rest) {
	return gcd(gcd(a, b), rest...);
}
#endif

// lcm, lowest common multiple
template<typename T>
inline T lcm(T a, T b) {
	return a / gcd(a, b) * b;
}
#ifdef __cpp11
template<typename T, typename ...Args>
inline T lcm(T a, T b, Args... rest) {
	return lcm(lcm(a, b), rest...);
}
#endif

// extend gcd
#if 0
// iterative edition
template<typename T>
inline T egcd(T a, T b, T& x, T& y) {
	std::stack<T> stk;
	T gcd;
	while (b != 0) {
		stk.push(a);
		T tmp = a % b;
		a = b;
		b = tmp;
	}
	gcd = a;
	x = 1;
	y = 0;
	while (!stk.empty()) {
		b = a;
		a = stk.top();
		stk.pop();
		T xx = y;
		T yy = x - (a / b) * y;
		x = xx;
		y = yy;
	}
	return gcd;
}
template<typename T>
inline T minv(T a, const T mod)
{
	return T();
}
#else
// brief recursive edition
template<typename T>
inline T egcd(T a, T b, T& x, T& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	T gcd = egcd(b, a % b, y, x);
	y -= (a / b) * x;
	return gcd;
}
#endif

//// 4 kinds of method to get modular multiplicative inverse

// the best, can avoid overflow using egcd
// modular multiplicative inverse using extend gcd, a and mod must be coprime.
template<typename T, typename U> inline T minv(T a, const U mod) {
	T x, y;
	T g = egcd(a, (T)(mod), x, y);
	assert(g == 1);
	return (x % mod + mod) % mod;
}

// another short modular multiplicative inverse, mod must be prime
// for any k != 0, ax = b (% mod) ==> kax = kb (% mod),
// but only when any k != 0 and mod are prime, or (k, mod) = 1, kax = kb (% mod) ==> ax = b (% mod)
// to calculate ax = 1 (% mod), suppose mod = pa + q, deduce:
// pax = p (% mod)
// (mod - q)x = p (% mod)
// qx = mod - p (% mod), so x = minv(q, mod) * (mod - p) % mod.
// a and mod must be coprime.
// if mod is too big, like 1e18+9 for long long type, this may overflow and get wrong answer.
template <typename T, typename U> inline T cil_minv(T a, U mod) {
	if (a == 1) return 1;
	return cil_minv(mod % a, mod) * (mod - mod / a) % mod;
}
// make sure a < mod.
template <typename T, typename U> inline T minv_brief(T a, U mod) {
	if (a > mod) a %= mod;
	return cil_minv(a, mod);
}

// modular multiplicative inverse using power(a, mod - 2, mod), mod must be prime.
// if mod is too big, like 1e18+9 for long long type, this may overflow and get wrong answer.
template<typename T, typename U> inline T minv_power(T a, U mod) {
	return power(a * 1LL, mod - 2, mod);
}

// modular multiplicative inverse using power(a, phi(mod) - 1, mod), (a, mod) = 1.
// if mod is too big, like 1e18+9 for long long type, this may overflow and get wrong answer.
template<typename T, typename U> inline T minv_power_phi(T a, U mod) {
	return power(a * 1LL, phi(mod) - 1, mod);
}


// Euler's phi function, or Euler's totient function
// counts the positive integers up to a given integer n that are
// relatively prime to n
template<typename T>
inline T phi(T n) {
	T ret = n;
	for (T i = 2; i * 1LL * i <= n; ++i) if (n % i == 0) {
		ret = ret / i * (i - 1);
		do n /= i; while (n % i == 0);
	}
	if (n > 1) ret = ret / n * (n - 1);
	return ret;
}

// quick power

template<typename T, typename U>
inline T power(T x, U n) {
	T ret = 1;
	while (n > 0) {
		if (n % 2) ret *= x;
		x *= x;
		n /= 2;
	}
	return ret;
}

template<typename T, typename U, typename V>
inline T power(T x, U n, V mod) {
	x %= mod;
	T ret = 1;
	while (n > 0) {
		if (n % 2) ret = ret * x % mod;;
		x = x * x % mod;
		n /= 2;
	}
	return ret;
}

// specialized for buildin integer type, so use bit operate to accelerate
template<typename T, typename V>
inline T power(T x, int n, V mod) {
	x %= mod;
	T ret = 1;
	while (n > 0) {
		if (n & 1) ret = ret * x % mod;;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}
template<typename T, typename V>
inline T power(T x, unsigned int n, V mod) {
	x %= mod;
	T ret = 1;
	while (n > 0) {
		if (n & 1) ret = ret * x % mod;;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

template<typename T, typename V>
inline T power(T x, long long n, V mod) {
	x %= mod;
	T ret = 1;
	while (n > 0) {
		if (n & 1) ret = ret * x % mod;;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

template<typename T, typename V>
inline T power(T x, unsigned long long n, V mod) {
	x %= mod;
	T ret = 1;
	while (n > 0) {
		if (n & 1) ret = ret * x % mod;;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}


// advanced modulo-multiply for positive integer by bits, to avoid overflow
template<typename T, typename U, typename V>
inline T bitmmul(T a, U b, V mod) {
	a %= mod;
	b %= mod;
	T ret = 0;
	while (b) {
		if (b & 1) if((ret += a) >= mod) ret -= mod;
		if ((a <<= 1) >= mod) a -= mod;
		b >>= 1;
	}
	return ret;
}

// advanced quick-modulo-power for positive integer by bits, to avoid overflow
template<typename T, typename U, typename V>
inline T bitmpow(T a, U n, V mod) {
	a %= mod;
	T ret = 1;
	while (n > 0) {
		if (n % 2 == 1) ret = bitmmul(ret, a, mod);
		a = bitmmul(a, a, mod);
		n /= 2;
	}
	return ret;
}

// miller-Rabin primality test

// for n < 4,759,123,141, (4,759,123,141 > 4 294 967 295)
inline bool Miller_Rabin(unsigned int n) {
	if (n == 2) return true;
	if ((~n & 1) || n == 1) return false;
	// form n - 1 = d * 2 ^ r//
	int d = (n - 1) >> 1; int r = 1;
	while (~d & 1) { d >>= 1; ++r; }
	unsigned int a[3] = { 2, 7, 61};
	for (int i = 0; i < 3; ++i) {
		if (a[i] == n) return true;
		unsigned int x = power((long long)(a[i]), d, n);
		if (x == 1 || x == n - 1) continue;
		// repeat r-1 times
		for (int k = 1; k < r; ++k) {
			x = 1ULL * x * x % n;
			if (x == 1) return false;
			if (x == n - 1) break;
		}
		if (x != n - 1) return false; // a^( (n-1)/2 )%n != 1 or n-1
	}
	return true;
}
inline bool Miller_Rabin(int n) {
	assert(n >= 0);
	return Miller_Rabin((unsigned int)(n));
}

// for n < 18,446,744,073,709,551,616 = 2^64
inline bool Miller_Rabin(unsigned long long n) {
	if (n == 2) return true;
	if ((~n & 1) || n == 1) return false;
	// form n - 1 = d * 2 ^ r//
	unsigned long long d = (n - 1) >> 1; int r = 1;
	while (~d & 1) { d >>= 1; ++r; }
	unsigned long long a[12] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 };
	for (int i = 0; i < 12; ++i) {
		if (a[i] == n) return true;
		unsigned long long x = bitmpow(a[i], d, n);
		if (x == 1 || x == n - 1) continue;
		// repeat r-1 times
		for (int k = 1; k < r; ++k) {
			x = bitmmul(x, x, n);
			if (x == 1) return false;
			if (x == n - 1) goto passed;
		}
		return false; // a^( (n-1)/2 )%n != 1 or n-1
	passed:;
	}
	return true;
}
inline bool Miller_Rabin(long long n) {
	assert(n >= 0);
	return Miller_Rabin((unsigned long long)(n));
}


// modular multiplicative inverse of a consecutive integers 1,2,3,...,n-1 modulo mod
// mod must be prime
inline void get_minv_array(int minv[], int n, const int mod) {
	minv[1] = 1;
	for (int i = 2; i < n; ++i)
		minv[i] = 1LL * minv[mod % i] * (mod - mod / i) % mod;
}

// sieve of Euler to get primes less than n, O(n)
inline void get_primes(int n, std::vector<int>& primes, std::vector<bool>& is_prime) {
	primes.clear();
	is_prime.clear();
	if (n <= 0) {
		return;
	}
	if (n <= 2) {
		is_prime.assign(n, false);
		return;
	}
	is_prime.resize(n, true);
	is_prime[0] = is_prime[1] = false;
	for (int i = 2; i < n; ++i) {
		if (is_prime[i]) primes.push_back(i);
		for (int j = 0; j < primes.size(); ++j) {
			long long t = 1LL * primes[j] * i;
			if (t >= n) break;
			is_prime[t] = false;
			if (i % primes[j] == 0) break;
		}
	}
}
inline void get_primes(int n, std::vector<int>& primes) {
	std::vector<bool> is_prime;
	is_prime.resize(n, true);
	for (int i = 2; i < n; ++i) {
		if (is_prime[i]) primes.push_back(i);
		for (int j = 0; j < primes.size(); ++j) {
			long long t = 1LL * primes[j] * i;
			if (t >= n) break;
			is_prime[t] = false;
			if (i % primes[j] == 0) break;
		}
	}
}
inline std::vector<int> get_primes(int n) {
	std::vector<int> primes;
	std::vector<bool> is_prime;
	is_prime.resize(n, true);
	for (int i = 2; i < n; ++i) {
		if (is_prime[i]) primes.push_back(i);
		for (int j = 0; j < primes.size(); ++j) {
			long long t = 1LL * primes[j] * i;
			if (t >= n) break;
			is_prime[t] = false;
			if (i % primes[j] == 0) break;
		}
	}
	return primes;
}

// calculate phi for integer 1, 2, 3, ... , n-1.
inline void get_phi_array(int n, std::vector<bool>& is_prime, std::vector<int>& primes, std::vector<int>& phi) {
	is_prime.clear(); is_prime.resize(n, true);
	primes.clear();
	phi.clear(); phi.resize(n);
	phi[1] = 1;
	for (int i = 2; i < n; ++i) {
		if (is_prime[i]) {
			primes.push_back(i);
			phi[i] = i - 1;
		}
		for (int j = 0; j < primes.size(); ++j) {
			long long t = 1LL * i * primes[j];
			if (t > n) break;
			is_prime[t] = false;
			if (i % primes[j]) {
				phi[t] = phi[i] * (primes[j] - 1);
			}
			else {
				phi[t] = phi[i] * primes[j];
				break;
			}
		}
	}
}
inline std::vector<int> get_phi_array(int n) {
	std::vector<bool> is_prime;
	std::vector<int> primes;
	std::vector<int> phi;
	get_phi_array(n, is_prime, primes, phi);
	return phi;
}

// sieve of Euler to get all prime numbers less than N
// as well as to judge if a number less than N is prime
template<int N> class sieve_of_Euler {
	static std::bitset<N> __is_prime;
	static std::vector<int> __primes;
	static bool __initialized;
public:
	static void init() {
		if (__initialized) return;
		__is_prime.set();
		__is_prime[0] = __is_prime[1] = false;
		__primes.clear();
		for (int i = 2; i < N; ++i) {
			if (__is_prime[i]) __primes.push_back(i);
			for (size_t j = 0; j < __primes.size(); ++j) {
				long long t = 1LL * i * __primes[j];
				if (t >= N) break;
				__is_prime[t] = false;
				if (i % __primes[j] == 0) break;
			}
		}
		__initialized = true;
	}
	static const std::bitset<N>& is_prime() {
		if (!__initialized) init();
		return __is_prime;
	}
	static const std::vector<int>& primes() {
		if (!__initialized) init();
		return __primes;
	}
	static bool is_prime(int i) {
		assert(i >= 0 && i < N);
		if (!__initialized) init();
		return __is_prime[i];
	}
	static int primes(int i) {
		if (!__initialized) init();
		assert(i >= 0 && i < __primes.size());
		return __primes[i];
	}
};
template<int N> bool sieve_of_Euler<N>::__initialized = false;
template<int N> std::bitset<N> sieve_of_Euler<N>::__is_prime;
template<int N> std::vector<int> sieve_of_Euler<N>::__primes;


// factorials and modular multiplicative of factorials, then could calc combinations using them
template<int MAX_FACT, int mod>
class factorial_and_combination {
	static bool __initialized;
	static int __fact[MAX_FACT], __inv_fact[MAX_FACT];
	static int mpow(int x, int k, int m) {
		int ret = 1;
		for (x %= m; k; k >>= 1) {
			if (k & 1) ret = 1LL * ret * x % m;
			x = 1LL * x * x % m;
		}
		return ret;
	}
public:
	factorial_and_combination() { init(); }
	static void init() {
		if (__initialized) return;
		__fact[0] = __inv_fact[0] = 1;
		for (int i = 1; i < MAX_FACT; ++i)
			__fact[i] = 1LL * i * __fact[i - 1] % mod;
		__inv_fact[MAX_FACT - 1] = mpow(__fact[MAX_FACT - 1], mod - 2, mod);
		for (int i = MAX_FACT - 2; i > 0; --i)
			__inv_fact[i] = 1LL * __inv_fact[i + 1] * (i + 1) % mod;
		__initialized = true;
	}
	static int fact(int i) { return __fact[i]; }
	static int inv_fact(int i) { return __inv_fact[i]; }
	static int C(int n, int m) {
		return 1LL * __fact[n] * __inv_fact[m] % mod * __inv_fact[n - m] % mod;
	}
};
template<int MAX_FACT, int mod>
bool factorial_and_combination<MAX_FACT, mod>::__initialized = false;
template<int MAX_FACT, int mod>
int factorial_and_combination<MAX_FACT, mod>::__fact[MAX_FACT];
template<int MAX_FACT, int mod>
int factorial_and_combination<MAX_FACT, mod>::__inv_fact[MAX_FACT];


// Yanghui triangle
template<int n, typename T = int, int mod = -1>
class Yanghui_triangle {
	T __C[n][n];
public:
	Yanghui_triangle() {
		for (int i = 0; i < n; ++i) {
			__C[i][0] = __C[i][i] = 1;
			for (int j = 1; j < i; ++j) { 
				__C[i][j] = __C[i - 1][j] + __C[i - 1][j - 1];
				__C[i][j] %= mod;
			}
		}
	}
	void display() {
		for (int i = 0; i < n; ++i) {
			std::cout << i << ": ";
			for (int j = 0; j < i; ++j) std::cout << __C[i][j] << " ";
			std::cout << __C[i][i] << std::endl;
		}
	}
	T C(int i, int j) { if (i >= n || j > i) return -1; return __C[i][j]; }
};

// specialized without modulo
template<int n, typename T> class Yanghui_triangle<n, T, -1> {
	T __C[n][n];
public:
	Yanghui_triangle() {
		for (int i = 0; i < n; ++i) {
			__C[i][0] = __C[i][i] = 1;
			for (int j = 1; j < i; ++j) {
				__C[i][j] = __C[i - 1][j] + __C[i - 1][j - 1];
			}
		}
	}
	void display() {
		for (int i = 0; i < n; ++i) {
			std::cout << i << ": ";
			for (int j = 0; j < i; ++j) std::cout << __C[i][j] << " ";
			std::cout << __C[i][i] << std::endl;
		}
	}
	T C(int i, int j) { if (i >= n || j > i) return -1; return __C[i][j]; }
};

// Josephus problem. 
// n people(0,1, ..., n-1) form a circle, start from 0, skip out one every k people.
// repeat n-1 times, calculate id of last one remained.
inline int Josephus(int n, int k) {
	std::stack<int> stk;
	while (n >= k) {
		stk.push(n);
		n -= n / k;
	}
	int ret = 0;
	for (int i = 2; i <= n; ++i) ret = (ret + k) % i;
	while (!stk.empty()) {
		n = stk.top();
		stk.pop();
		int r = n % k;
		if (ret < r) ret = ret - r + n;
		else ret = ret - r + (ret - r) / (k - 1);
	}
	return ret;
}

/* eof */
#endif
