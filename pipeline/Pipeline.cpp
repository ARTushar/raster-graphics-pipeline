//
// Created by tushar on 5/18/21.
//

#include <iostream>
#include "Pipeline.h"

using namespace std;

Pipeline::Pipeline() {
    input_file_name = "../test-cases/3/scene.txt";
    input_file.open(input_file_name);
    parse_view_input();
    parse_projection_input();
}

void Pipeline::parse_input_file() {
    string cd;
    while (true) {
        input_file >> cd;
        cout << "command: " << cd << endl;
        COMMAND command = Command::generate_command(cd);
        if(command == END || command == INVALID) break;
        parse_command(command);
    }
    clipping.run();
    clipping.print_z_buffer();
}

void Pipeline::parse_command(const COMMAND &command) {
    switch (command) {
        case TRIANGLE:
            parse_triangle();
            break;
        case TRANSLATE:
            parse_translate();
            break;
        case SCALE:
            parse_scale();
            break;
        case ROTATE:
            parse_rotate();
            break;
        case PUSH:
            parse_push();
            break;
        case POP:
            parse_pop();
            break;
        default:
            break;
    }
}

Pipeline::~Pipeline() {
    input_file.close();
}

void Pipeline::parse_triangle() {
    double p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z;
    input_file >> p1x >> p1y >> p1z >> p2x >> p2y >> p2z >> p3x >> p3y >> p3z;
    vector<Matrix> list =  model.parse_triangle({p1x, p1y, p1z}, {p2x, p2y, p2z}, {p3x, p3y, p3z});
//    vector<Point> points;
    for(auto &m: list) {
        Matrix vm = view.apply_view_transformation(m);
        Matrix pr = projection.apply_projection(vm);
//        points.push_back(Matrix::toPoint(pr));
    }
    view.write_nl();
    projection.write_nl();
//    clipping.scan_triangle(points[0], points[1], points[2]);
}

void Pipeline::parse_translate() {
    double tx, ty, tz;
    input_file >> tx >> ty >> tz;
    model.parse_translate(tx, ty, tz);
}

void Pipeline::parse_scale() {
    double sx, sy, sz;
    input_file >> sx >> sy >> sz;
    model.parse_scale(sx, sy, sz);
}

void Pipeline::parse_rotate() {
    double angle, ax, ay, az;
    input_file >> angle >> ax >> ay >> az;
    model.parse_rotate(angle, {ax, ay, az});
}

void Pipeline::parse_push() {
    model.parse_push();
}

void Pipeline::parse_pop() {
    model.parse_pop();
}

void Pipeline::parse_view_input() {
    double ex, ey, ez, lx, ly, lz, ux, uy, uz;
    input_file >> ex >> ey >> ez >> lx >> ly >> lz >> ux >> uy >> uz;
    view.set_view_matrix({ex, ey, ez}, {lx, ly, lz}, {ux, uy, uz});
}

void Pipeline::parse_projection_input() {
    double fov_y, ratio, near, far;
    input_file >> fov_y >> ratio >> near >> far;
    projection.set_projection_attributes(fov_y, ratio, near, far);
}
