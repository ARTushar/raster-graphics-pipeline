//
// Created by tushar on 5/18/21.
//

#ifndef RASTERPIPELINE_PIPELINE_H
#define RASTERPIPELINE_PIPELINE_H


#include "model/Model.h"
#include "../utils/command/Command.h"
#include "view/View.h"
#include "projection/Projection.h"
#include "clipping/Clipping.h"

class Pipeline {
private:
    Model model;
    View view;
    Projection projection;
    Clipping clipping;
    std::string input_file_name;
    std::ifstream input_file;
    void parse_command(const COMMAND &command);
    void parse_triangle();
    void parse_translate();
    void parse_scale();
    void parse_rotate();
    void parse_push();
    void parse_pop();
    void parse_view_input();

public:
    Pipeline();
    virtual ~Pipeline();
    void parse_input_file();
    void parse_projection_input();
};


#endif //RASTERPIPELINE_PIPELINE_H
