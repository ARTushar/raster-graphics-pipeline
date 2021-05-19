//
// Created by tushar on 5/18/21.
//

#ifndef RASTERPIPELINE_MATRIX_H
#define RASTERPIPELINE_MATRIX_H

class Matrix {
private:
    const int row;
    const int col;
public:
    double matrix[4][4];

    Matrix();
    Matrix(const int &row, const int &col);
    Matrix mul(const Matrix &m);
    Matrix add(const Matrix &m);
    Matrix set_diagonals(const double &dx, const double &dy, const double &dz);
    Matrix set_rmc(const double &dx, const double &dy, const double &dz);
    Matrix set_mlc(const double &dx, const double &dy, const double &dz);
    Matrix set_mrc(const double &dx, const double &dy, const double &dz);
    Matrix set_lmc(const double &dx, const double &dy, const double &dz);
};


#endif //RASTERPIPELINE_MATRIX_H
