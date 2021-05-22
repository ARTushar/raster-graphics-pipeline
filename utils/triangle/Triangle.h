//
// Created by tushar on 5/22/21.
//

#ifndef RASTERPIPELINE_TRIANGLE_H
#define RASTERPIPELINE_TRIANGLE_H


#include "../point/Point.h"

class Triangle {
private:
    static double get_x_at_y_line(const double &y, const double &x1, const double &y1, const double &x2, const double &y2);
    static bool y_intersects_line(const double &y, const double &y1, const double &y2);
    static int get_random_color();
public:
    Point points[3];
    int color[3];
    double max_y, min_y;
    double current_x_a, current_x_b, current_z_a, current_z_b, current_z_p;
    std::string min_line, max_line;

    Triangle(const Point &a, const Point &b, const Point &c);
    void set_max_y();
    void set_min_y();
    void set_max_min_x_at_y(const double &y);
    void set_za_zb_zp(const double &y);
    void initial_scan_at_y(const double &y);
    double get_z_at_x_y(const double &del_x, const double &y) const;
    static void test();
};


#endif //RASTERPIPELINE_TRIANGLE_H
