//
// Created by Shuangquan Li on 20/09/2018.
//

#ifndef __GEOMETRY_POINT_H__
#define __GEOMETRY_POINT_H__

#include <cmath>
#include <functional>
#include <iostream>

namespace cil {


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
    bool operator < (const point& B) const { return x < B.x || (x == B.x && y < B.y); }
    bool operator > (const point& B) const { return x > B.x || (x == B.x && y > B.y); }
    bool operator <= (const point& B) const { return x < B.x || (x == B.x && y <= B.y); }
    bool operator >= (const point& B) const { return x > B.x || (x == B.x && y >= B.y); }
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

namespace std {
template<typename T>
struct hash<point<T> > {
    size_t operator()(const point<T> &p) const {
        return std::hash<T>{}((std::hash<T>{}(p.x) * 19921211) ^ (std::hash<T>{}(p.y) * 2147483647));
    }
};
}

template<typename T> double distance(const point<T>& A, const point<T>& B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}
template<typename T> double distance(T x1, T y1, T x2, T y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

}

#endif //__GEOMETRY_POINT_H__
