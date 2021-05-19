//
// Created by tushar on 5/18/21.
//

#include <iostream>
#include "Pipeline.h"

Pipeline::Pipeline() {
    input_file_name = "input/scene.txt";
    input_file.open(input_file_name);
}

void Pipeline::parse_input_file() {
    std::string cd;
    while (true) {
        input_file >> cd;
        std::cout << "command: " << cd << std::endl;
        COMMAND command = Command::generate_command(cd);
        if(command == END || command == INVALID) break;
        parse_command(command);
    }
}

void Pipeline::parse_command(const COMMAND &command) {
    switch (command) {
        case TRIANGLE:
            parse_triangle();
            break;
    }
}

Pipeline::~Pipeline() {
    input_file.close();
}

void Pipeline::parse_triangle() {
    double p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z;
    input_file >> p1x >> p1y >> p1z >> p2x >> p2y >> p2z >> p3x >> p3y >> p3z;
    model.parse_triangle_command({p1x, p1y, p1z}, {p2x, p2y, p2z}, {p3x, p3y, p3z});
}
