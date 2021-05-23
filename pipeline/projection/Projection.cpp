//
// Created by tushar on 5/18/21.
//

#include <iomanip>
#include <iostream>
#include "Projection.h"
#include "../../utils/transformation/Transformation.h"

#define PI (2 * acos(0.0))

Projection::Projection(): output_file_name("output/stage3.txt") {
    output_file.open(output_file_name);
    output_file << fixed;
    output_file << setprecision(7);
}

void Projection::set_projection_attributes(const double &fov_y, const double &ratio, const double &near, const double &far) {
    auto fov_x = fov_y * ratio;
    auto t = near * tan(fov_y / 2 * PI / 180);
    auto r = near * tan(fov_x / 2 * PI / 180);
    projection_matrix = Transformation::get_projection_matrix(near, far, r, t);
}

Matrix Projection::apply_projection(const Matrix &m) {
    Matrix result = projection_matrix.mul(m);
    result.normalize();
    result.write_to_file(output_file);
    return result;
}

void Projection::write_nl() {
    output_file << endl;
}
