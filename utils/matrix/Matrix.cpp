//
// Created by tushar on 5/18/21.
//

#include <iostream>
#include "Matrix.h"

Matrix::Matrix() : row {4}, col{4}, matrix { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 1}} {
}

Matrix::Matrix(const int &row, const int &col): row {row}, col {col} {
    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            matrix[i][j] = 0;
        }
    }
    matrix[row-1][col-1] = 1;
}

Matrix Matrix::mul(const Matrix &m) {
    if (col != m.row) {
        std::cout << "Invalid mul" << std::endl;
        return Matrix();
    }

    Matrix result(row, m.col);

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < m.col; j++) {
            result.matrix[i][j] = 0;
            for(int k = 0; k < col; k++) {
                result.matrix[i][j] += matrix[i][k] * m.matrix[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::add(const Matrix &m) {
    if(row != m.row || col != m.col) {
        std::cout << "Invalid add" << std::endl;
        return Matrix();
    }

    Matrix result;

    for(int i = 0; i < row; i++) {
        for(int j = 0; j < col; j++) {
            result.matrix[i][j] = matrix[i][j] + m.matrix[i][j];
        }
    }
    return result;
}

void Matrix::set_diagonals(const double &dx, const double &dy, const double &dz) {
    if(row != 4 || col != 4) {
        std::cout << "invalid set diagonals" << std::endl;
    }
    matrix[0][0] = dx;
    matrix[1][1] = dy;
    matrix[2][2] = dz;
}

void Matrix::set_rmc(const double &dx, const double &dy, const double &dz) {
    if(row != 4 || col != 4) {
        std::cout << "invalid set rmc" << std::endl;
    }
    matrix[0][col-1] = dx;
    matrix[1][col-1] = dy;
    matrix[2][col-1] = dz;
}

void Matrix::set_mlc(const double &dx, const double &dy, const double &dz) {
    if(row != 4 || col != 4) {
        std::cout << "invalid set mlc" << std::endl;
    }
    matrix[0][1] = dx;
    matrix[1][1] = dy;
    matrix[2][1] = dz;
}

void Matrix::set_lmc(const double &dx, const double &dy, const double &dz) {
    if(row != 4 || col != 4) {
        std::cout << "invalid set lmc" << std::endl;
    }
    matrix[0][0] = dx;
    matrix[1][0] = dy;
    matrix[2][0] = dz;
}

void Matrix::set_mrc(const double &dx, const double &dy, const double &dz) {
    if(row != 4 || col != 4) {
        std::cout << "invalid set mrc" << std::endl;
    }
    matrix[0][2] = dx;
    matrix[1][2] = dy;
    matrix[2][2] = dz;
}

Matrix Matrix::identity(const int &row, const int &col) {
    Matrix iden(row, col);
    iden.set_diagonals(1, 1, 1);
    return iden;
}

void Matrix::write_to_file(std::ofstream &output) {
    for(int i = 0; i < row-1; i++) {
        for(int j = 0; j < col-1 || j == 0; j++) {
            output << matrix[i][j] << " ";
        }
        output << std::endl;
    }
    output << std::endl;
}

Matrix::Matrix(const Point &point): row{4}, col{1} {
    matrix[0][0] = point.x;
    matrix[1][0] = point.y;
    matrix[2][0] = point.z;
    matrix[3][0] = 1;
}
