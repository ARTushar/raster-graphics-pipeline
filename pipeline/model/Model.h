//
// Created by tushar on 5/18/21.
//

#ifndef RASTERPIPELINE_MODEL_H
#define RASTERPIPELINE_MODEL_H

#include <stack>
#include <string>
#include <fstream>
#include "../../utils/matrix/Matrix.h"
#include "../../utils/point/Point.h"

class Model {
private:
    std::stack<Matrix> transformations;
    std::string output_file;
    std::ofstream output;

    void transform_point(const Point &point);

public:
    Model();
    virtual ~Model();
    void parse_triangle_command(const Point &point1, const Point &point2, const Point &point3);
};


#endif //RASTERPIPELINE_MODEL_H
