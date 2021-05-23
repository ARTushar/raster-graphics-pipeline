//
// Created by tushar on 5/22/21.
//

#include <iostream>
#include "Triangle.h"
using namespace std;

Triangle::Triangle(const Point &a, const Point &b, const Point &c):
        points {a, b, c}, color {Triangle::get_random_color(), Triangle::get_random_color(), Triangle::get_random_color()}
{
    set_max_y();
    set_min_y();
}

void Triangle::set_max_y() {
    max_y = max(max(points[0].y, points[1].y), points[2].y);
}

void Triangle::set_min_y() {
    min_y = min(min(points[0].y, points[1].y), points[2].y);
}

void Triangle::set_max_min_x_at_y(const double &y) {
    double max_x = -MAXFLOAT;
    double min_x = MAXFLOAT;
    double val;
    double val_max, val_min;

    if(y == points[0].y && y == points[1].y){
        val_max = max(points[0].x, points[1].x);
        val_min = min(points[0].x, points[1].x);
        if(val_max > max_x) {
            max_x = val_max;
            max_line = "01";
        }
        if(val_min < min_x) {
            min_x = val_min;
            min_line = "01";
        }
    }
    else if(y_intersects_line(y, points[0].y, points[1].y)){
        val = get_x_at_y_line(y, points[0].x, points[0].y, points[1].x, points[1].y);
        if(val > max_x ) {
            max_x = val;
            max_line = "01";
        }
        if(val < min_x) {
            min_x = val;
            min_line = "01";
        }
    }

    if(y == points[1].y && y == points[2].y){
        val_max = max(points[1].x, points[2].x);
        val_min = min(points[1].x, points[2].x);
        if(val_max > max_x) {
            max_x = val_max;
            max_line = "12";
        }
        if(val_min < min_x) {
            min_x = val_min;
            min_line = "12";
        }
    }
    else if(y_intersects_line(y, points[1].y, points[2].y)){
        val = get_x_at_y_line(y, points[1].x, points[1].y, points[2].x, points[2].y);
        if(val > max_x ) {
            max_x = val;
            max_line = "12";
        }
        if(val < min_x) {
            min_x = val;
            min_line = "12";
        }
    }
    if(y == points[2].y && y == points[0].y){
        val_max = max(points[2].x, points[0].x);
        val_min = min(points[2].x, points[0].x);
        if(val_max > max_x) {
            max_x = val_max;
            max_line = "20";
        }
        if(val_min < min_x) {
            min_x = val_min;
            min_line = "20";
        }
    }
    else if(y_intersects_line(y, points[2].y, points[0].y)){
        val = get_x_at_y_line(y, points[2].x, points[2].y, points[0].x, points[0].y);
        if(val > max_x ) {
            max_x = val;
            max_line = "20";
        }
        if(val < min_x) {
            min_x = val;
            min_line = "20";
        }
    }
    if(max_x == -MAXFLOAT) {
        cout << "Max x is invalid!" << endl;
    }
    if(min_x == MAXFLOAT) {
        cout << "Min x is invalid!" << endl;
    }
    current_x_b = max_x;
    current_x_a = min_x;
}

int Triangle::get_random_color() {
    return rand() % 255;
}

double Triangle::get_x_at_y_line(const double &y, const double &x1, const double &y1, const double &x2, const double &y2) {
    return x1 + ((y - y1) * (x2 - x1)) / (y2 - y1);
}

bool Triangle::y_intersects_line(const double &y, const double &y1, const double &y2) {
    return  (y >= y1 && y <= y2) || (y >= y2 && y <= y1);
}

double Triangle::get_z_at_x_y(const double &x, const double &y) const {
    double del_x = x - current_x_a;
    if(current_x_b == current_x_a) return current_z_p;
    return current_z_p + del_x * (current_z_b - current_z_a) / (current_x_b - current_x_a);
}

void Triangle::set_za_zb_zp(const double &y) {
    int min_ix_0 = min_line[0] - '0';
    int min_ix_1 = min_line[1] - '0';
    int max_ix_0 = max_line[0] - '0';
    int max_ix_1 = max_line[1] - '0';
    if(min_line == max_line) {
        if(points[min_ix_0].z < points[min_ix_1].z) {
            current_z_a = points[min_ix_0].z;
            current_z_b = points[min_ix_1].z;
            current_z_p = current_z_a;
        } else {
            current_z_a = points[min_ix_1].z;
            current_z_b = points[min_ix_0].z;
            current_z_p = current_z_a;
        }
        return;
    }
    int common_ix = -1;
    int min_ix = -1, max_ix = -1;

    if(max_ix_0 == min_ix_0) {
        common_ix = max_ix_0;
        min_ix = min_ix_1;
        max_ix = max_ix_1;
    }
    else if(max_ix_0 == min_ix_1) {
        common_ix = max_ix_0;
        min_ix = min_ix_0;
        max_ix = max_ix_1;
    }
    else if(max_ix_1 == min_ix_0) {
        common_ix = max_ix_1;
        min_ix = min_ix_1;
        max_ix = max_ix_0;
    }
    else {
        common_ix = max_ix_1;
        min_ix = min_ix_0;
        max_ix = max_ix_0;
    }
//    cout << "min_ix_0: " << min_ix_0 << " min_ix_1: " << min_ix_1 << " max_ix_0: " << max_ix_0 << " max_ix_1: " << max_ix_1 << endl;
    if(common_ix == min_ix && common_ix == max_ix) {
//        cout << "single point" << endl;
        current_z_a = points[common_ix].z;
        current_z_b = current_z_a;
        current_z_p = current_z_a;
        return;
    }

    current_z_a = points[common_ix].z + (y - points[common_ix].y) / (points[min_ix].y - points[common_ix].y) * (points[min_ix].z - points[common_ix].z);
    current_z_b = points[common_ix].z + (y - points[common_ix].y) / (points[max_ix].y - points[common_ix].y) * (points[max_ix].z - points[common_ix].z);;
    current_z_p = current_z_a;
}

void Triangle::initial_scan_at_y(const double &y) {
//    cout << "y:" << y << endl;
    set_max_min_x_at_y(y);
//    printf("minx: %f max x: %f max_line: %s min_line: %s\n", current_x_a, current_x_b, max_line.c_str(), min_line.c_str());
    set_za_zb_zp(y);
//    printf("currentza: %f currentzb: %f\n", current_z_a, current_z_b);
}

void Triangle::test() {
    Triangle triangle({10, 10, 10}, {1, 0, 0}, {0, 1, 0});
    printf("min_y: %f, max_y: %f\n", triangle.min_y, triangle.max_y);
    for(auto y = triangle.min_y; y <= triangle.max_y; y = y + 0.5){
        triangle.initial_scan_at_y(y);
        for(auto x = triangle.current_x_a; x <= triangle.current_x_b; x += 0.5) {
            printf("at x = %f, calculated z: %f\n", x, triangle.get_z_at_x_y(x - triangle.current_x_a, y));
        }
    }
}