//
// Created by tushar on 5/18/21.
//

#ifndef RASTERPIPELINE_MATRIX_H
#define RASTERPIPELINE_MATRIX_H


class Matrix {
private:
    static const int len = 4;
public:
    double matrix[len][len];

    Matrix();
    Matrix mul(const Matrix &m);
    Matrix add(const Matrix &m);
    Matrix set_diagonals(const double &dx, const double &dy, const double &dz);
    Matrix set_rmc(const double &dx, const double &dy, const double &dz);
    Matrix set_mc(const double &dx, const double &dy, const double &dz);
    Matrix set_lmc(const double &dx, const double &dy, const double &dz);
};


#endif //RASTERPIPELINE_MATRIX_H
