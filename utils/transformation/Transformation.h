//
// Created by tushar on 5/18/21.
//

#ifndef RASTERPIPELINE_TRANSFORMATION_H
#define RASTERPIPELINE_TRANSFORMATION_H

#include "../matrix/Matrix.h"
#include "../point/Point.h"

class Transformation {
private:
    static Point apply_rodrigues_formula(const Point &axis, const double &rotation_angle, const Point &rotating_vector);
public:
    Transformation();
    static Matrix get_scale_matrix(const double &sx, const double &sy, const double &sz);
    static Matrix get_translate_matrix(const double &tx, const double &ty, const double &tz);
    static Matrix get_rotate_matrix(const double &rotation_angle, const Point &rotating_vector);
    static Matrix get_view_translate_matrix(const Point &eye);
    static Matrix get_view_rotate_matrix(const Point &r, const Point &u, const Point &l);
    static Matrix get_projection_matrix(const double &near, const double &far, const double &r, const double &t);
};


#endif //RASTERPIPELINE_TRANSFORMATION_H
