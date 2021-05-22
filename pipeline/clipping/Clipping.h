//
// Created by tushar on 5/22/21.
//

#ifndef RASTERPIPELINE_CLIPPING_H
#define RASTERPIPELINE_CLIPPING_H


#include <string>
#include <fstream>
#include "../../utils/point/Point.h"

using namespace std;

class Clipping {
private:
    string output_file_name;
    ofstream output_file;
public:
    double **z_buffer;
    double **frame_buffer;
    double top_limit, bottom_limit, right_limit, left_limit, front_limit, rear_limit;
    int screen_width, screen_height;
    double top_y, left_x;
    double dx, dy, z_max;

    Clipping();
    void set_config(const int &screen_width, const int &screen_height, const double &left_limit,
                    const double &bottom_limit, const double &front_limit, const double &rear_limit);
    void scan_triangle(const Point &a, const Point &b, const Point &c);
    void allocate_buffers();
    void delete_buffers() const;
};


#endif //RASTERPIPELINE_CLIPPING_H
