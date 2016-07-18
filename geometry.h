/*
 * geometry header.
 * written by Shuangquan Li, lishq991@gmail.com
 * created on 2016-5-17
 */

#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__
#include <cmath>
#include <algorithm>


// point on a two-dimensional plane
//struct Point {
//	double x, y;
//	Point(double a, double b): x(a), y(b) {}
//};

// distance of two point
//double distance(const Point &a, const Point &b) {
//	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
//}
//template<typename T> double distance(T x1, T y1, T x2, T y2) {
//	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
//}


// intersection aera of two circle
//double intersection_area(const Point &a, double r1, const Point &b, double r2) {
//	double d = distance(a, b);
//	if (d + 1e-9 >= r1 + r2) return 0;
//	if (d <= fabs(r1 - r2) + 1e-9) {
//		double r = min(r1, r2);
//		return acos(-1) * r * r;
//	}
//	double x = (r1 * r1 + d * d - r2 * r2) / (2 * d);
//	double alpha1 = acos(x / r1);
//	double alpha2 = acos((d - x) / r2);
//	return alpha1 * r1 * r1 + alpha2 * r2 *r2 - d * r1 * sin(alpha1);
//}


/* eof */
#endif