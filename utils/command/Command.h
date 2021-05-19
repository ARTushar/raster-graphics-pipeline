//
// Created by tushar on 5/19/21.
//

#ifndef RASTERPIPELINE_COMMAND_H
#define RASTERPIPELINE_COMMAND_H


#include <string>

enum COMMAND {
    TRIANGLE,
    TRANSLATE,
    SCALE,
    ROTATE,
    PUSH,
    POP,
    END,
    INVALID
};

class Command {
public:
    static COMMAND generate_command(std::string command) {
        if(command == "triangle") return TRIANGLE;
        if(command == "translate") return TRANSLATE;
        if(command == "scale") return SCALE;
        if(command == "rotate") return ROTATE;
        if(command == "push") return PUSH;
        if(command == "pop") return POP;
        if(command == "end") return END;
        return INVALID;
    }
};


#endif //RASTERPIPELINE_COMMAND_H
