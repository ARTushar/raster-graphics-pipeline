//
// Created by tushar on 5/18/21.
//

#ifndef RASTERPIPELINE_MODEL_H
#define RASTERPIPELINE_MODEL_H

#include <stack>
#include <string>
#include <fstream>
#include <vector>
#include "../../utils/matrix/Matrix.h"
#include "../../utils/point/Point.h"
#include "../../utils/command/Command.h"

class Model {
private:
    std::stack<Matrix> transformations;
    std::string output_file;
    std::ofstream output;
    int current_stack_index;
    std::stack<int> last_push_index;

    Matrix transform_point(const Point &point);

public:
    Model();
    virtual ~Model();
    std::vector<Matrix> parse_triangle(const Point &point1, const Point &point2, const Point &point3);
    void parse_translate(const double &tx, const double &ty, const double &tz);
    void parse_scale(const double &sx, const double &sy, const double &sz);
    void parse_rotate(const double &rotate_angle, const Point &rotation_axis);
    void parse_push();
    void parse_pop();
};


#endif //RASTERPIPELINE_MODEL_H
