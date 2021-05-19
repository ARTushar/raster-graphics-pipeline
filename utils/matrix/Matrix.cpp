//
// Created by tushar on 5/18/21.
//

#include <iostream>
#include "Matrix.h"

using namespace std;

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
        cout << "Invalid mul" << endl;
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
        cout << "Invalid add" << endl;
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
        cout << "invalid set diagonals" << endl;
    }
    matrix[0][0] = dx;
    matrix[1][1] = dy;
    matrix[2][2] = dz;
}

void Matrix::set_rmc(const double &dx, const double &dy, const double &dz) {
    if(row != 4 || col != 4) {
        cout << "invalid set rmc" << endl;
    }
    matrix[0][col-1] = dx;
    matrix[1][col-1] = dy;
    matrix[2][col-1] = dz;
}

void Matrix::set_mlc(const double &dx, const double &dy, const double &dz) {
    if(row != 4 || col != 4) {
        cout << "invalid set mlc" << endl;
    }
    matrix[0][1] = dx;
    matrix[1][1] = dy;
    matrix[2][1] = dz;
}

void Matrix::set_lmc(const double &dx, const double &dy, const double &dz) {
    if(row != 4 || col != 4) {
        cout << "invalid set lmc" << endl;
    }
    matrix[0][0] = dx;
    matrix[1][0] = dy;
    matrix[2][0] = dz;
}

void Matrix::set_mrc(const double &dx, const double &dy, const double &dz) {
    if(row != 4 || col != 4) {
        cout << "invalid set mrc" << endl;
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

void Matrix::write_to_file(ofstream &output) {
    if(col == 1) write_vector(output);
    else write_matrix(output);
}

Matrix::Matrix(const Point &point): row{4}, col{1} {
    matrix[0][0] = point.x;
    matrix[1][0] = point.y;
    matrix[2][0] = point.z;
    matrix[3][0] = 1;
}

void Matrix::write_vector(ofstream &output) {
    for(int i = 0; i < row-1; i++) {
        output << matrix[i][0];
        if(i != row-2) output << " ";
    }
    output << endl;
}

void Matrix::write_matrix(ofstream &output) {
    for(int i = 0; i < row-1; i++) {
        for(int j = 0; j < col-1; j++) {
            output << matrix[i][j];
            if(j != col-2) output << " ";
        }
        output << endl;
    }
    output << endl;
}

Matrix Matrix::combine_vectors(const Matrix &v1, const Matrix &v2, const Matrix &v3) {
    if(!(v1.row == 4 && v1.col == 1 && v2.row == 4 && v2.col == 1 && v3.row == 4 && v3.col == 1)) {
        cout << "Invalid matrix formation from vectors" << endl;
        return Matrix();
    }
    Matrix result;
    result.set_lmc(v1.matrix[0][0], v1.matrix[1][0], v1.matrix[2][0]);
    result.set_mlc(v2.matrix[0][0], v2.matrix[1][0], v2.matrix[2][0]);
    result.set_mrc(v3.matrix[0][0], v3.matrix[1][0], v3.matrix[2][0]);
}

void Matrix::normalize() {
    if(!(row == 4 && col == 1)){
        return;
    }

    if(matrix[3][0] != 1)  {
        auto scale = matrix[3][0];
        if(scale == 0) {
            cout << "w is zero!!" << endl;
            return;
        }
        for(int i = 0; i < row; i++) {
            matrix[i][0] /= scale;
        }
    }
}

