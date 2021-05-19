//
// Created by tushar on 5/18/21.
//

#ifndef RASTERPIPELINE_PROJECTION_H
#define RASTERPIPELINE_PROJECTION_H

#include <string>
#include <fstream>
#include "../../utils/matrix/Matrix.h"

using namespace std;

class Projection {
private:
    string output_file_name;
    ofstream output_file;
    Matrix projection_matrix;
public:
    Projection();
    void set_projection_attributes(const double &fov_y, const double &ratio, const double &near, const double &far);
    Matrix apply_projection(const Matrix &m);
    void write_nl();
};


#endif //RASTERPIPELINE_PROJECTION_H
