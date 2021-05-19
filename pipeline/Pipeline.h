//
// Created by tushar on 5/18/21.
//

#ifndef RASTERPIPELINE_PIPELINE_H
#define RASTERPIPELINE_PIPELINE_H


#include "model/Model.h"
#include "../utils/command/Command.h"

class Pipeline {
private:
    Model model;
    std::string input_file_name;
    std::ifstream input_file;
    void parse_command(const COMMAND &command);
    void parse_triangle();

public:
    Pipeline();

    virtual ~Pipeline();

    void parse_input_file();
};


#endif //RASTERPIPELINE_PIPELINE_H
