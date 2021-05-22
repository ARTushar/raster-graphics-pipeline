//
// Created by tushar on 5/22/21.
//

#include <iomanip>
#include "Clipping.h"

Clipping::Clipping(): output_file_name("output/z-buffer.txt") {
    output_file.open(output_file_name);
    output_file << fixed;
    output_file << setprecision(7);
}

void Clipping::set_config(const int &scr_width, const int &scr_height, const double &lt_lim,
                          const double &btm_lim, const double &frt_lim, const double &rear_lim) {
    screen_width = scr_width;
    screen_height = scr_height;
    left_limit = lt_lim;
    right_limit = -lt_lim;
    bottom_limit = btm_lim;
    top_limit = -btm_lim;
    dx = (right_limit - left_limit) / screen_width;
    dy = (top_limit - bottom_limit) / screen_height;
    top_y = top_limit - dy/2;
    left_x = left_limit + dx/2;
    front_limit = frt_lim;
    rear_limit = rear_lim;
    z_max = rear_limit;
    allocate_buffers();
}

void Clipping::allocate_buffers() {
    z_buffer = new double *[screen_width];
    frame_buffer = new double *[screen_width];
    for(int i = 0; i < screen_width; i++) {
        z_buffer[i] = new double [screen_height];
        for(int j = 0; j < screen_height; j++) {
            z_buffer[i][j] = z_max;
        }
        frame_buffer[i] = new double [screen_height];
    }
}

void Clipping::delete_buffers() const {
    for(int i = 0; i < screen_width; i++) {
        delete [] z_buffer[i];
        delete [] frame_buffer[i];
    }
    delete [] z_buffer;
    delete [] frame_buffer;
}

