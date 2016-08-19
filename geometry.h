/*
 * geometry header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-5-17
 * last edit on 2016-8-19
 */

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "cil_config.h"
#include <cmath>
#include <deque>
#include <vector>
#include <algorithm>
#include <iterator>

// line in 2D plane, y = k * x + b
template<typename T> struct line {
	T k, b;
	line() {}
	line(T kk, T bb) : k(kk), b(bb) {}
	T at(T x) const { return k * x + b; }
	bool operator < (const line& rhs) const {
		return k < rhs.k || k == rhs.k && b < rhs.b;
	}
};
template<typename T> std::ostream& operator<< (std::ostream& os, const line<T>& l) {
	return os << "(" << l.k << ", " << l.b << ")" << std::flush;
}

// convex hull trick formed with line.
// to get the max/min y with a specified x among a lot of lines.
template<typename T>
class convex_hull_trick_line {
	typedef line<T> Line;
	std::deque<Line> ql;
	// x coordinate of intersections is ascending.
	bool check(const Line& a, const Line& b, const Line& c) const {
		return (b.b - a.b) * (b.k - c.k) < (c.b - b.b) * (a.k - b.k);
	}
public:
	void clear() { ql.clear(); }
	size_t size() const { return ql.size(); }
	// make sure k of lines pushed is ordered and distinct.
	// for k in ascending order to query_max only. concave.
	// for k in descending order to query_min only. convex.
	void push(T k, T b) { push(Line(k, b)); }
	void push(const std::pair<T, T>& kb) { push(Line(kb.first, kb.second)); }
	void push(const Line& l) {
		while (ql.size() >= 2 && !check(ql[(int)(ql.size()) - 2], ql.back(), l))
			ql.pop_back();
		ql.push_back(l);
	}
	// make sure x of querys is in non-decreasing order. left to right.
	T query_max(T x) {
		while (ql.size() >= 2 && ql[0].at(x) <= ql[1].at(x))
			ql.pop_front();
		return ql[0].at(x);
	}
	T query_min(T x) {
		while (ql.size() >= 2 && ql[0].at(x) >= ql[1].at(x))
			ql.pop_front();
		return ql[0].at(x);
	}
};


// point in 2D plane
template<typename T>
struct point {
	T x, y;
	point() {}
	point(T xx, T yy) : x(xx), y(yy) {}
	point(const point& B) : x(B.x), y(B.y) {}
	double radius() const { return sqrt(x * x + y *y); }
	double angle() const { return atan2(y, x); }
	double angle_degree() const { return atan2(y, x) * 180 / 3.14159265358979323846264338327950288419716939937510; }
	bool operator == (const point& B) const { return x == B.x && y == B.y; }
	bool operator != (const point& B) const { return x != B.x || y != B.y; }
	bool operator < (const point& B) const { return x < B.x || x == B.x && y < B.y; }
	bool operator > (const point& B) const { return x > B.x || x == B.x && y > B.y; }
	bool operator <= (const point& B) const { return x < B.x || x == B.x && y <= B.y; }
	bool operator >= (const point& B) const { return x > B.x || x == B.x && y >= B.y; }
	point& operator = (const point& B) { x = B.x; y = B.y; return *this; }
	point operator + (const point& B) const { return point(x + B.x, y + B.y); }
	point operator - (const point& B) const { return point(x - B.x, y - B.y); }
	point& operator += (const point& B) { x += B.x; y += B.y; return *this; }
	point& operator -= (const point& B) { x -= B.x; y -= B.y; return *this; }
	T operator * (const point& B) const { return x * B.x + y * B.y; }
	T operator ^ (const point& B) const { return x * B.y - y * B.x; }
};
template<typename T> std::ostream& operator<< (std::ostream& os, const point<T>& p) {
	return os << "(" << p.x << ", " << p.y << ")" << std::flush;
}

template<typename T> double distance(const point<T>& A, const point<T>& B) {
	return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}
template<typename T> double distance(T x1, T y1, T x2, T y2) {
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


// get vonvex hull among a lot of unoredred points.
// the first point of result is the left-down-most one, others formed in anticolckwise order.

// one implementation is find the left-down-most one as an origin point, then sort others by angle
// of the vector from the origin to other points each. then scan all points once.
#ifndef __cpp11
template<typename PointType>
struct __CompareHelperForGraham {
	PointType o;
	__CompareHelperForGraham(PointType p) : o(p) {}
	bool operator() (const PointType& a, const PointType& b) const {
		return (a - o).angle() < (b - o).angle();
	}
};
#endif
template<typename RandomAccessIterator, typename OutputIterator>
int Graham(RandomAccessIterator first, RandomAccessIterator last, OutputIterator output) {
	RandomAccessIterator it = first + 1;
	for (; it != last; ++it) if (*it < *first) swap(*first, *it);
	typedef typename std::iterator_traits<RandomAccessIterator>::value_type value_type;
#ifdef __cpp11
	auto cmp = [&](const value_type& a, const value_type& b) {
		return (a - *first).angle() < (b - *first).angle();
	};
#else
	__CompareHelperForGraham<value_type> cmp(*first);
#endif
	std::sort(first + 1, last, cmp);
	int cnt = 0;
	it = first;
	output[cnt++] = *it++;
	while (it != last) {
		while (cnt >= 2 && ((output[cnt - 1] - output[cnt - 2]) ^ (*it - output[cnt - 1])) <= 0) --cnt;
		output[cnt++] = *it++;
	}
	return cnt;
}

// another implementation is sort all points by x, y in pair<x, y> order, then scan all points left
// to right once to get the lower hull and scan all points right to left twice to get the upper hull.
template<typename RandomAccessIterator, typename OutputIterator>
int Graham2(RandomAccessIterator first, RandomAccessIterator last, OutputIterator output) {
	std::sort(first, last);
	int cnt = 0;
	RandomAccessIterator it = first;
	output[cnt++] = *it++;
	while (it != last) {
		while (cnt >= 2 && ((output[cnt - 1] - output[cnt - 2]) ^ (*it - output[cnt - 1])) <= 0) --cnt;
		output[cnt++] = *it++;
	}
	it -= 2;
	while (it != first) {
		while (cnt >= 2 && ((output[cnt - 1] - output[cnt - 2]) ^ (*it - output[cnt - 1])) <= 0) --cnt;
		output[cnt++] = *it--;
	}
	while (cnt >= 2 && ((output[cnt - 1] - output[cnt - 2]) ^ (*it - output[cnt - 1])) <= 0) --cnt;
	return cnt;
}

template<typename RandomAccessIterator>
std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type>
Graham(RandomAccessIterator first, RandomAccessIterator last) {
	std::vector<iterator_traits<RandomAccessIterator>::value_type> ret(last - first);
	int n = Graham(first, last, ret.begin());
	ret.resize(n);
	return ret;
}
template<typename Container>
Container Graham(Container& c) {
	Container ret(c.size());
	int n = Graham(c.begin(), c.end(), ret.begin());
	ret.resize(n);
	return ret;
}
//template<typename T> std::vector<point<T>> Graham(std::vector<point<T>>& p) {
//	std::vector<point<T>> ret;
//	int n = p.size();
//	std::sort(p.begin(), p.end());
//	for (int i = 0; i < n; ++i) {
//		while (ret.size() >= 2 && ((ret.back() - ret[(int)(ret.size()) - 2]) ^ (p[i] - ret.back())) <= 0)
//			ret.pop_back();
//		ret.push_back(p[i]);
//	}
//	for (int i = n - 1; i >= 0; --i) {
//		while (ret.size() >= 2 && ((ret.back() - ret[(int)(ret.size()) - 2]) ^ (p[i] - ret.back())) <= 0)
//			ret.pop_back();
//		ret.push_back(p[i]);
//	}
//	ret.pop_back();
//	return ret;
//}


// calculate polygon area, points in clockwise/anticlockwise order
template<typename RandomAccessIterator>
double polygon_area(const RandomAccessIterator& first, const RandomAccessIterator& last) {
	int n = last - first;
	if (n < 3) return 0;
	double ret = 0;
	for (int i = 0; i < n - 1; ++i)
		ret += first[i] ^ first[i + 1];
	ret += first[n - 1] ^ first[0];
	return abs(ret * 0.5);
}
template<typename Container>
double polygon_area(const Container& c) {
	return polygon_area(c.begin(), c.end());
}


// triangle in 2D plane
template<typename T> struct triangle {
	typedef point<T> Point;
	Point A, B, C;
	triangle() {};
	triangle(const Point& a, const Point& b, const Point& c) : A(a), B(b), C(c) {}
	double area() const {
		double a = distance(B, C);
		double b = distance(A, C);
		double c = distance(A, B);
		double l = (a + b + c) * 0.5;
		return sqrt(l * (l - a) * (l - b) * (l - c));
	}
};

template<typename T> double triangle_area(const point<T>& A, const point<T>& B, const point<T>& C) {
	double a = distance(B, C);
	double b = distance(A, C);
	double c = distance(A, B);
	double l = (a + b + c) * 0.5;
	return sqrt(l * (l - a) * (l - b) * (l - c));
}
template<typename T> double triangle_area(T Ax, T Ay, T Bx, T By, T Cx, T Cy) {
	return triangle_area(point<T>(Ax, Ay), point<T>(Bx, By), point<T>(Cx, Cy));
}

// circle in 2D plane
template<typename T> struct circle {
	T x, y, r;
	circle() {}
	circle(T xx, T yy, T rr) : x(xx), y(yy), r(rr) {}
	circle(const point<T>& o, T rr) : x(o.x), y(o.y), r(rr) {}
	point<T> center() const { return point<T>(x, y); }
};
// distance of two circle
template<typename T> double distance(const circle<T>& o1, const circle<T>& o2) {
	return distance(o1.center(), o2.center());
}
// intersection aera of two circle
template<typename T> double intersection_area(const circle<T>& o1, const circle<T>& o2, const double eps = 1e-9) {
	double d = distance(o1, o2);
	double r1 = o1.r, r2 = o2.r;
	if (d + eps >= r1 + r2) return 0;
	if (d <= fabs(r1 - r2) + eps) {
		double r = min(r1, r2);
		return acos(-1) * r * r;
	}
	double x = (r1 * r1 + d * d - r2 * r2) / (2 * d);
	double alpha1 = acos(x / r1);
	double alpha2 = acos((d - x) / r2);
	return alpha1 * r1 * r1 + alpha2 * r2 *r2 - d * r1 * sin(alpha1);
}
template<typename T> double intersection_area(const point<T>& o1, T r1, const const point<T>& o2, T r2, const double eps = 1e-9) {
	return intersection_area(circle<T>(o1, r1), circle<T>(o2, r2), eps);
}


/* eof */
#endif
