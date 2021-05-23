//
// Created by tushar on 5/22/21.
//

#ifndef RASTERPIPELINE_CLIPPING_H
#define RASTERPIPELINE_CLIPPING_H


#include <string>
#include <fstream>
#include "../../utils/point/Point.h"
#include "../../utils/image/bitmap_image.hpp"

using namespace std;

class Clipping {
private:
    string input_file_name;
    string output_file_name;
    ofstream output_file;
    ifstream input_file;
public:
    double **z_buffer{};
    double top_limit{}, bottom_limit{}, right_limit{}, left_limit{}, front_limit{}, rear_limit{};
    int screen_width{}, screen_height{};
    double top_y{}, left_x{}, bottom_y{}, right_x{};
    double dx{}, dy{}, z_max{};
    bitmap_image *image;

    Clipping();
    void parse_input();
    virtual ~Clipping();
    void set_config();
    void scan_triangle(const Point &a, const Point &b, const Point &c) const;
    void print_z_buffer();
    void allocate_buffers();
    void delete_buffers() const;
};


#endif //RASTERPIPELINE_CLIPPING_H
