//
// Created by tushar on 5/22/21.
//

#include <iomanip>
#include <iostream>
#include "Clipping.h"
#include "../../utils/triangle/Triangle.h"

Clipping::Clipping(): output_file_name("output/z-buffer.txt"), input_file_name("../test-cases/3/config.txt"), input_triangles_file_name("output/stage3.txt") {
    input_file.open(input_file_name);
    input_triangles_file.open(input_triangles_file_name);
    output_file.open(output_file_name);
    output_file << fixed;
    output_file << setprecision(6);
    parse_input();
    set_config();
}

void Clipping::set_config() {
    right_limit = -left_limit;
    top_limit = -bottom_limit;
    dx = (right_limit - left_limit) / screen_width;
    dy = (top_limit - bottom_limit) / screen_height;
    top_y = top_limit - dy/2;
    bottom_y = bottom_limit + dy/2;
    left_x = left_limit + dx/2;
    right_x = right_limit - dx/2;
    z_max = rear_limit;
    allocate_buffers();
}

void Clipping::allocate_buffers() {
    printf("Allocating buffers\n");
    z_buffer = new double *[screen_width];
    for(int i = 0; i < screen_width; i++) {
        z_buffer[i] = new double [screen_height];
        for(int j = 0; j < screen_height; j++) {
            z_buffer[i][j] = z_max;
        }
    }
    image = new bitmap_image(screen_width, screen_height);
}

void Clipping::delete_buffers() const {
    printf("Deallocating buffers\n");
    for(int i = 0; i < screen_width; i++) {
        delete [] z_buffer[i];
    }
    delete [] z_buffer;
    delete image;
}

Clipping::~Clipping() {
    input_file.close();
    input_triangles_file.close();
    output_file.close();
    delete_buffers();
}

void Clipping::scan_triangle(const Point &a, const Point &b, const Point &c) const {
    Triangle triangle(a, b, c);
    int top_scan_line = ceil((top_y -  min(top_y, triangle.max_y)) / dy);
    int bottom_scan_line = floor((top_y - max(bottom_y, triangle.min_y)) / dy);
//    double top_scan_line = min(top_y, triangle.max_y);
//    double bottom_scan_line = max(bottom_y, triangle.min_y);
//    for(auto scan_line = top_scan_line; scan_line >= bottom_scan_line; scan_line -= dy) {
//        triangle.initial_scan_at_y(scan_line);
//        double left_col =  max(left_x, triangle.current_x_a);
//        double right_col = min(right_x, triangle.current_x_b);
//        int row = round ((top_y - scan_line) / dy);
//        for(auto col = left_col; col <= right_col; col += dx) {
//            double z_value = triangle.get_z_at_x_y(col, scan_line);
//            int col_ix = round ((col - left_x) / dx);
//            if(z_value >= front_limit && z_value < z_buffer[row][col_ix]) {
//                z_buffer[row][col_ix] = z_value;
//                image->set_pixel(col_ix, row, triangle.color[0], triangle.color[1], triangle.color[2]);
//            }
//        }
//    }
    for(auto row = top_scan_line; row < bottom_scan_line; row++) {
        triangle.initial_scan_at_y(top_y - row * dy);
        int left_col =  ceil((max(left_x, triangle.current_x_a) - left_x) / dx);
        int right_col = floor((min(right_x, triangle.current_x_b) - left_x) / dx);
        for(auto col = left_col; col < right_col; col++) {
            double z_value = triangle.get_z_at_x_y(left_x + col * dx, top_y - row * dy);
            if(z_value >= front_limit && z_value < z_buffer[row][col]) {
                z_buffer[row][col] = z_value;
                image->set_pixel(col, row, triangle.color[0], triangle.color[1], triangle.color[2]);
            }
        }
    }
}

void Clipping::print_z_buffer() {
    for(int i = 0; i < screen_height; i++) {
        for (int j = 0; j < screen_width; j++) {
            if(z_buffer[i][j] < z_max) {
                output_file << z_buffer[i][j];
                if(j != screen_width - 1) output_file << "\t";
            }
        }
        output_file << endl;
    }
    image->save_image("output/output.bmp");
}

void Clipping::parse_input() {
    input_file >> screen_width >> screen_height >> left_limit >> bottom_limit >> front_limit >> rear_limit;
    printf("config inputs %d %d %f %f %f %f\n", screen_width, screen_height, left_limit, bottom_limit, front_limit, rear_limit);
}

void Clipping::run() {
    double x1, y1, z1, x2, y2, z2, x3, y3, z3;
    while(input_triangles_file >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3) {
        Point a{x1, y1, z1}, b{x2, y2, z2}, c{x3, y3, z3};
        scan_triangle(a, b, c);
    }
}
