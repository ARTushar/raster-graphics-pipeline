//
// Created by tushar on 5/18/21.
//

#include "Transformation.h"

#define PI (2 * acos(0.0))

Transformation::Transformation() {

}

Matrix Transformation::get_scale_matrix(const double &sx, const double &sy, const double &sz) {}(const double &sx, const double &sy, const double &sz) {
    Matrix scale_matrix;
    scale_matrix.set_diagonals(sx, sy, sz);
    return scale_matrix;
}

Matrix Transformation::get_translate_matrix(const double &tx, const double &ty, const double &tz) {
    Matrix translate_matrix;
    translate_matrix.set_diagonals(1, 1, 1);
    translate_matrix.set_rmc(tx, ty, tz);
    return translate_matrix;
}

Matrix Transformation::get_rotate_matrix(const double &rotation_angle, const Point &rotating_vector) {
    Point normalized_vector = rotating_vector.normalize();
    Point c1 = apply_rodrigues_formula({1, 0, 0}, rotation_angle, normalized_vector);
    Point c2 = apply_rodrigues_formula({0, 1, 0}, rotation_angle, normalized_vector);
    Point c3 = apply_rodrigues_formula({0, 0, 1}, rotation_angle, normalized_vector);
    Matrix result;
    result.set_lmc(c1.x, c1.y, c1.z);
    result.set_mc(c2.x, c2.y, c2.z);
    result.set_rmc(c3.x, c3.y, c3.z);
    return result;
}

Point Transformation::apply_rodrigues_formula(const Point &axis, const double &rotation_angle, const Point &rotating_vector) {
    double cos_theta = cos(rotation_angle * PI / 180);
    double sin_theta = sin(rotation_angle * PI / 180);
    Point result = axis * cos_theta +
                   rotating_vector * ((1 - cos_theta) * (rotating_vector.dot(axis))) +
                   rotating_vector.cross(axis) * sin_theta;
    return result;
}