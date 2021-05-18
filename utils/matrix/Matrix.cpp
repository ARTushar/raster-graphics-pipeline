//
// Created by tushar on 5/18/21.
//

#include "Matrix.h"

Matrix::Matrix() : matrix{ {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}} {
}

Matrix Matrix::mul(const Matrix &m) {
    Matrix result;
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            result.matrix[i][j] = 0;
            for(int k = 0; k < len; k++) {
                result.matrix[i][j] += matrix[i][k] * m.matrix[k][j];
            }
        }
    }
    retrun result;
}

Matrix Matrix::add(const Matrix &m) {
    Matrix result;
    for(int i = 0; i < len; i++) {
        for(int j = 0; j < len; j++) {
            result.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
        }
    }
    return  result;
}

Matrix Matrix::set_diagonals(const double &dx, const double &dy, const double &dz) {
    matrix[0][0] = dx;
    matrix[1][1] = dy;
    matrix[2][2] = dz;
}

Matrix Matrix::set_rmc(const double &dx, const double &dy, const double &dz) {
    matrix[0][len-1] = dx;
    matrix[1][len-1] = dy;
    matrix[2][len-1] = dz;
}

Matrix Matrix::set_mc(const double &dx, const double &dy, const double &dz) {
    matrix[0][1] = dx;
    matrix[1][1] = dy;
    matrix[2][1] = dz;
}

Matrix Matrix::set_lmc(const double &dx, const double &dy, const double &dz) {
    matrix[0][0] = dx;
    matrix[1][0] = dy;
    matrix[2][0] = dz;
}
