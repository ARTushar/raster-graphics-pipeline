//
// Created by tushar on 5/18/21.
//

#include <iostream>
#include <iomanip>
#include "View.h"
#include "../../utils/transformation/Transformation.h"
using namespace std;

Matrix View::apply_view_transformation(const Matrix &m) {
    Matrix result = view_matrix.mul(m);
    result.write_to_file(output_file);
    result.normalize();
    return result;
}

void View::set_view_matrix(const Point &eye, const Point &look, const Point &up) {
    l = look - eye;
    l = l.normalize();
    r = l.cross(up);
    r = r.normalize();
    u = r.cross(l);
    view_matrix = Transformation::get_view_rotate_matrix(r, u, l).mul(
            Transformation::get_view_translate_matrix(eye)
    );
}

View::View(): output_file_name("output/stage2.txt") {
    output_file.open(output_file_name);
    output_file << fixed;
    output_file << setprecision(7);
}

View::~View() {
    output_file.close();
}

void View::write_nl() {
    output_file << endl;
}
