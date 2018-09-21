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
class point {
    T __x, __y;

public:
    point(): __x(0), __y(0) {}
    point(T x, T y) : __x(x), __y(y) {}
    point(const point& p) : __x(p.__x), __y(p.__y) {}

    T x() const { return __x; }
    T y() const { return __y; }

    double radius() const { return sqrt(__x * __x + __y *__y); }
    double angle() const { return atan2(__y, __x); }
    double angle_degree() const { return atan2(__y, __x) * 180 / 3.14159265358979323846264338327950288419716939937510; }

    bool operator == (const point& B) const { return __x == B.__x && __y == B.__y; }
    bool operator != (const point& B) const { return __x != B.__x || __y != B.__y; }
    bool operator < (const point& B) const { return __x < B.__x || (__x == B.__x && __y < B.__y); }
    bool operator > (const point& B) const { return __x > B.__x || (__x == B.__x && __y > B.__y); }
    bool operator <= (const point& B) const { return __x < B.__x || (__x == B.__x && __y <= B.__y); }
    bool operator >= (const point& B) const { return __x > B.__x || (__x == B.__x && __y >= B.__y); }

    point& operator = (const point& B) { __x = B.__x; __y = B.__y; return *this; }
    point operator + (const point& B) const { return point(__x + B.__x, __y + B.__y); }
    point operator - (const point& B) const { return point(__x - B.__x, __y - B.__y); }
    point& operator += (const point& B) { __x += B.__x; __y += B.__y; return *this; }
    point& operator -= (const point& B) { __x -= B.__x; __y -= B.__y; return *this; }
    T operator * (const point& B) const { return __x * B.__x + __y * B.__y; }
    T operator ^ (const point& B) const { return __x * B.__y - __y * B.__x; }
};

template<typename T> std::ostream& operator<< (std::ostream& os, const point<T>& p) {
    return os << "(" << p.x() << ", " << p.y() << ")" << std::flush;
}


template<typename T> double distance(const point<T>& A, const point<T>& B) {
    return sqrt((A.x() - B.x()) * (A.x() - B.x()) + (A.y() - B.y()) * (A.y() - B.y()));
}

template<typename T> double distance(T x1, T y1, T x2, T y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

} // namespace cil


namespace std {

template<typename T>
struct hash<cil::point<T> > {
    size_t operator()(const cil::point<T>& p) const {
        return std::hash<T>{}((std::hash<T>{}(p.x()) * 19921211) ^ (std::hash<T>{}(p.y()) * 2147483647));
    }
};

} // namespace std

#endif //__GEOMETRY_POINT_H__
