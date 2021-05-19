//
// Created by tushar on 5/18/21.
//

#include <iostream>
#include <iomanip>
#include "Model.h"
#include "../../utils/transformation/Transformation.h"
using namespace std;

Model::Model(): output_file("output/stage1.txt"), current_stack_index {0} {
    transformations.push(Matrix::identity());
    output.open(output_file);
    output << fixed;
    output << setprecision(7);
}

Model::~Model() {
    output.close();
}

vector<Matrix> Model::parse_triangle(const Point &point1, const Point &point2, const Point &point3) {
    Matrix res1 = transform_point(point1);
    Matrix res2 = transform_point(point2);
    Matrix res3 = transform_point(point3);
    output << endl;
    vector<Matrix> list;
//    cout << "1: " << res1.row << " " << res1.col << endl;
//    cout << "2: " << res2.row << " " << res2.col << endl;
//    cout << "3: " << res3.row << " " << res3.col << endl;
    list.push_back(res1);
    list.push_back(res2);
    list.push_back(res3);
    return list;
}

Matrix Model::transform_point(const Point &point) {
    Matrix point_matrix(point);
    Matrix result = transformations.top().mul(point_matrix);
    result.write_to_file(output);
    return result;
}

void Model::parse_translate(const double &tx, const double &ty, const double &tz) {
    Matrix translation_matrix = Transformation::get_translate_matrix(tx, ty, tz);
    transformations.push(transformations.top().mul(translation_matrix));
    current_stack_index++;
}

void Model::parse_scale(const double &sx, const double &sy, const double &sz) {
    Matrix scale_matrix = Transformation::get_scale_matrix(sx, sy, sz);
    transformations.push(transformations.top().mul(scale_matrix));
    current_stack_index++;
}

void Model::parse_rotate(const double &rotate_angle, const Point &rotation_axis) {
    Matrix rotate_matrix = Transformation::get_rotate_matrix(rotate_angle, rotation_axis);
    transformations.push(transformations.top().mul(rotate_matrix));
    current_stack_index++;
}

void Model::parse_push() {
    if(!last_push_index.empty() && last_push_index.top() == current_stack_index) {
        cout << "Invalid Push" << endl;
        return;
    }

    last_push_index.push(current_stack_index);
}

void Model::parse_pop() {
    if(last_push_index.empty()) {
        cout << "Invalid pop" << endl;
        return;
    }

    auto last_state_index = last_push_index.top();
    auto diff = current_stack_index - last_state_index;

    while(diff--) {
        transformations.pop();
    }
}