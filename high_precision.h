/*
 * high precision header
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-1-6
 */

#ifndef __HIGH_PRECISION_H__
#define __HIGH_PRECISION_H__

#include <assert.h>
#include <string>
#include <algorithm>
using std::string;


class HP {
	int s;      // sign : 1 or -1
	string v;   // absolute value string
public:
	HP(): v("0"), s(1) {}
	HP(const HP&b) : s(b.s), v(b.v) {}
	HP(string a, int b) : v(a), s(b) {}
	HP(string str) { if (str[0] == '-') { s = -1; v = str.substr(1); } else { s = 1; v = str; } }
	HP(long long x) {
		if (x == LLONG_MIN) { s = -1; v = "9223372036854775808"; return; }
		if (x < 0) { s = -1; x *= -1ll ; }
		else s = 1;
		do { int t = x % 10; v += (char)('0' + t); x /= 10; } while (x);
		std::reverse(v.begin(), v.end());
	}	
	int sign() const { return s; }
	string str() const { return s == 1 ? v : '-' + v; }
	bool operator == (const HP & b) const { return s == b.s && v == b.v; }
	bool operator != (const HP & b) const { return s != b.s || v != b.v; }
	bool operator < (const HP & b) const {
		if (s != b.s) return s < b.s;
		return s > 0 ? isGreater(b.v, v) : isGreater(v, b.v);
	}
	bool operator > (const HP & b) const { return (*this != b) && !(*this < b); }
	bool operator <= (const HP & b) const { return (*this) == b || (*this) < b; }
	bool operator >= (const HP & b) const { return !(*this < b); }

	HP abs() const { return HP(v, 1); }
	HP & flip() { s *= -1; return *this; }
	HP operator - () const { return HP(v, -s); }
	HP & operator = (const HP & b) { s = b.s; v = b.v; return *this; }
	void clear() { s = 1; v = "0"; }

	HP operator + (const HP & b) const {
		if (s == b.s) { return HP(add(v, b.v), s); }
		if (s > 0) return isGE(v, b.v) ? HP(sub(v, b.v), 1) : HP(sub(b.v, v), -1);
		else return isLE(v, b.v) ? HP(sub(b.v, v), 1) : HP(sub(v, b.v), -1);
	}
	HP & operator += (const HP & b) { return *this = *this + b; }
	HP operator - (const HP & b) const { return *this + (-b); }
	HP & operator -= (const HP & b) { return *this += (-b); }
	HP operator * (const HP & b) const { return HP(mul(v, b.v), s * b.s); }
	HP & operator *= (const HP & b) { return *this = HP(mul(v, b.v), s * b.s); }
	HP operator / (const HP & b) const { return HP(div(v, b.v).first, s / b.s); }
	HP & operator /= (const HP & b) { return *this = HP(div(v, b.v).first, s / b.s); }
	HP operator % (const HP & b) const { return HP(div(v, b.v).second, s); }
	HP & operator %= (const HP & b) { return *this = HP(div(v, b.v).second, s); }
	friend std::ostream& operator << (std::ostream & os, const HP & b) { os << b.str(); return os; }
private:
	inline bool isGreater(const string &a, const string &b) const {
		size_t na = a.size(), nb = b.size();
		if (na != nb) return na > nb;
		for (size_t i = 0; i < na; ++i) if (a[i] != b[i]) return a[i] > b[i];
		return false;
	}
	inline bool isEqual(const string &a, const string &b) const { return a == b; }
	inline bool isGE(const string &a, const string &b) const { return isGreater(a, b) || isEqual(a, b); }
	inline bool isLess(const string &a, const string &b) const { return !isGE(a, b); }
	inline bool isLE(const string &a, const string &b) const { return isLess(a, b) || isEqual(a, b); }
	inline string add(const string & a, const string & b) const {
		string ret;
		int up = 0;
		int i = int(a.size()) - 1;
		int j = int(b.size()) - 1;
		while (i >= 0 || j >= 0) {
			int sum = up;
			if (i >= 0) sum += a[i--] - '0';
			if (j >= 0) sum += b[j--] - '0';
			up = sum / 10;
			sum -= up * 10;
			ret += sum + '0';
		}
		if (up) ret += '1';
		std::reverse(ret.begin(), ret.end());
		return ret;
	}
	inline string sub(const string & a, const string & b) const {
		//assert(a.size() >= b.size());
		if (a == b) return string{ "0" };
		string ret;
		int up = 0;
		int i = int(a.size()) - 1;
		int j = int(b.size()) - 1;
		while (i >= 0 || j >= 0) {
			int diff = a[i--] - '0' - up;
			if (j >= 0) diff -= b[j--] - '0';
			if (diff < 0) { diff += 10; up = 1; }
			else up = 0;
			ret += diff + '0';
		}
		while (ret.back() == '0') ret.pop_back();
		std::reverse(ret.begin(), ret.end());
		return ret;
	}
	inline string mul(const string & a, const string & b) const {
		string sum(a.size() + b.size(), '0');
		for (int i = int(a.size()) - 1; i >= 0; --i) {
			int up = 0;
			for (int j = int(b.size()) - 1; 0 <= j; --j) {
				int t = (sum[i + j + 1] - '0') + (a[i] - '0') * (b[j] - '0') + up;
				up = t / 10;
				sum[i + j + 1] = t - up * 10 + '0';
			}
			sum[i] += up;
		}
		size_t startpos = sum.find_first_not_of("0");
		if (startpos != string::npos) return sum.substr(startpos);
		return string{ "0" };
	}
	inline std::pair<string, string> div(const string & a, const string & b) const {
		if (b == "1") return std::make_pair(a, "0");
		int m = int(a.size()), n = int(b.size());
		string q, r = a.substr(0, n);
		for (int i = n - 1; i < m; ++i) {
			int cnt = 0;
			while (isGE(r, b)) {
				++cnt;
				r = sub(r, b);
			}
			q += cnt + '0';
			if (i < m - 1) {
				if (r == "0") r = a[i + 1];
				else r += a[i + 1];
			}
		}
		size_t startpos = q.find_first_not_of("0");
		if (startpos != string::npos) return std::make_pair(q.substr(startpos), r);
		return std::make_pair("0", r);
	}
};




/* eof */
#endif