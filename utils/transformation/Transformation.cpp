//
// Created by tushar on 5/18/21.
//

#include "Transformation.h"

#define PI (2 * acos(0.0))

Transformation::Transformation() {

}

Matrix Transformation::get_scale_matrix(const double &sx, const double &sy, const double &sz) {
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

Matrix Transformation::get_rotate_matrix(const double &rotation_angle, const Point &rotation_axis) {
    Point normalized_axis = rotation_axis.normalize();
    Point c1 = apply_rodrigues_formula({1, 0, 0}, normalized_axis, rotation_angle) ;
    Point c2 = apply_rodrigues_formula({0, 1, 0}, normalized_axis, rotation_angle);
    Point c3 = apply_rodrigues_formula({0, 0, 1}, normalized_axis, rotation_angle);
    Matrix result;
    result.set_lmc(c1.x, c1.y, c1.z);
    result.set_mlc(c2.x, c2.y, c2.z);
    result.set_mrc(c3.x, c3.y, c3.z);
    return result;
}

Matrix Transformation::get_view_rotate_matrix(const Point &r, const Point &u, const Point &l) {
    Matrix result;
    result.set_lmc(r.x, u.x, -l.x);
    result.set_mlc(r.y, u.y, -l.y);
    result.set_mrc(r.z, u.z, -l.z);
    return result;
}

Matrix Transformation::get_view_translate_matrix(const Point &eye) {
    Matrix result;
    result.set_diagonals(1, 1, 1);
    result.set_rmc(-eye.x, -eye.y, -eye.z);
    return result;
}

Matrix Transformation::get_projection_matrix(const double &near, const double &far, const double &r, const double &t) {
    Matrix result;
    result.matrix[3][2] = -1;
    result.matrix[3][3] = 0;
    result.matrix[2][3] = -(2 * far * near) / (far - near);
    result.set_diagonals(near/r, near/t, -(far+near)/(far-near));
    return result;
}

Point Transformation::apply_rodrigues_formula(const Point &rotating_vector, const Point &axis, const double &rotation_angle) {
    double cos_theta = cos(rotation_angle * PI / 180);
    double sin_theta = sin(rotation_angle * PI / 180);
    Point result = rotating_vector * cos_theta +
                   axis * ((1 - cos_theta) * (axis.dot(rotating_vector))) +
                   axis.cross(rotating_vector) * sin_theta;
    return result;
}
