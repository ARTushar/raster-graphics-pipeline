//
// Created by tushar on 5/18/21.
//

#ifndef RASTERPIPELINE_POINT_H
#define RASTERPIPELINE_POINT_H

#include <cmath>

class Point{

public:

    double x, y, z;
    Point()= default;
    Point(double x, double y, double z) : x{ x }, y{ y }, z{ z } {}

    double dot(const Point & rhs) const {
      return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    Point normalize() const {
        double total = sqrt(x*x + y*y + z*z);
        double new_x = x / total;
        double new_y = y / total;
        double new_z = z / total;
        return {new_x, new_y, new_z};
    }

    Point cross(const Point & rhs) const {
        double new_x = y * rhs.z - z * rhs.y;
        double new_y = z * rhs.x - x * rhs.z;
        double new_z = x * rhs.y - y * rhs.x;
        return {new_x, new_y, new_z};
    }

    double distance(const Point & rhs) const{
        return sqrt(pow(x-rhs.x, 2) + pow(y-rhs.y, 2) + pow(z-rhs.z, 2));
    }

    Point operator * (double a) const {
        return {x*a, y*a, z*a};
    }

    Point operator + (Point a) const {
        return {x + a.x, y + a.y, z + a.z};
    }

    Point operator - (Point a) const {
        return {x - a.x, y - a.y, z - a.z};
    }

    bool operator<(const Point &rhs) const {
        if (x < rhs.x)
            return true;
        if (rhs.x < x)
            return false;
        if (y < rhs.y)
            return true;
        if (rhs.y < y)
            return false;
        return z < rhs.z;
    }

    bool operator>(const Point &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Point &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Point &rhs) const {
        return !(*this < rhs);
    }

    bool operator==(const Point &rhs) const {
        return x == rhs.x &&
               y == rhs.y &&
               z == rhs.z;
    }

    bool operator!=(const Point &rhs) const {
        return !(rhs == *this);
    }
};


#endif //RASTERPIPELINE_POINT_H
