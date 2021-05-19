//
// Created by tushar on 5/18/21.
//

#include <iostream>
#include "Model.h"

Model::Model(): output_file("output/stage1.txt") {
    transformations.push(Matrix::identity());
    output.open(output_file);
}

Model::~Model() {
    output.close();
}

void Model::parse_triangle_command(const Point &point1, const Point &point2, const Point &point3) {
    transform_point(point1);
    transform_point(point2);
    transform_point(point3);
}

void Model::transform_point(const Point &point) {
    Matrix point_matrix(point);
    Matrix result = transformations.top().mul(point_matrix);
    result.write_to_file(output);
}

