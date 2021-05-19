//
// Created by tushar on 5/18/21.
//

#ifndef RASTERPIPELINE_VIEW_H
#define RASTERPIPELINE_VIEW_H


#include "../../utils/point/Point.h"
#include "../../utils/matrix/Matrix.h"

class View {
private:
    Point l{}, r{}, u{};
    Matrix view_matrix;
    std::string output_file_name;
    std::ofstream output_file;
public:
    View();
    virtual ~View();
    void set_view_matrix(const Point &eye, const Point &look, const Point &up);
    Matrix apply_view_transformation(const Matrix &m);
    void write_nl();
};


#endif //RASTERPIPELINE_VIEW_H
