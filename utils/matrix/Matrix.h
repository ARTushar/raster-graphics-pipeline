//
// Created by tushar on 5/18/21.
//

#ifndef RASTERPIPELINE_MATRIX_H
#define RASTERPIPELINE_MATRIX_H

#include <fstream>
#include "../point/Point.h"

class Matrix {
private:
    const int row;
    const int col;
public:
    double matrix[4][4];

    Matrix();
    Matrix(const int &row, const int &col);
    Matrix(const Point &point);
    Matrix mul(const Matrix &m);
    Matrix add(const Matrix &m);
    void set_diagonals(const double &dx, const double &dy, const double &dz);
    void set_rmc(const double &dx, const double &dy, const double &dz);
    void set_mlc(const double &dx, const double &dy, const double &dz);
    void set_mrc(const double &dx, const double &dy, const double &dz);
    void set_lmc(const double &dx, const double &dy, const double &dz);
    static Matrix identity(const int &row=4, const int &col=4);
    void write_to_file(std::ofstream &output);
};


#endif //RASTERPIPELINE_MATRIX_H
