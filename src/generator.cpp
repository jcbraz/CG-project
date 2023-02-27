#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define GLUT_

struct GeometricFigure {
    std::string graphicType;
    double radius_or_length;
    int slices_or_grid;
    int stacks;
    std::string outputFile;
};

GeometricFigure parseThreeCoordenateInput(std::string commands) {
    std::stringstream input(commands);
    std::string token;
    std::vector<std::string> tokens;
    while (input >> token) {
        tokens.push_back(token);
    }

    GeometricFigure input_struct;
    if (tokens.size() == 6) {
        input_struct.graphicType = tokens[1];
        input_struct.radius_or_length = std::stod(tokens[2]);
        input_struct.slices_or_grid = std::stoi(tokens[3]);
        input_struct.stacks = std::stoi(tokens[4]);
        input_struct.outputFile = tokens[5];
    } else if (tokens.size() == 5) {
        input_struct.graphicType = tokens[1];
        input_struct.radius_or_length = std::stod(tokens[2]);
        input_struct.slices_or_grid = std::stoi(tokens[3]);
        input_struct.stacks = -1;
        input_struct.outputFile = tokens[4];
    }
    return input_struct;
}

void executeCommands(GeometricFigure input_struct) {

    GLUquadric* quad = gluNewQuadric();
    if (input_struct.graphicType == "sphere") {
        gluSphere(quad,input_struct.radius_or_length, input_struct.slices_or_grid, input_struct.stacks);
        gluDeleteQuadric(quad);
    } else if (input_struct.graphicType == "box") {
    } else if (input_struct.graphicType == "cone") {
    } else if (input_struct.graphicType == "plane") {
    } else {
        std::cout << "Invalid Graphic Type";
    }

    glFlush();
}


// Para executar, ir para a pasta build, "make group_project", "./group_project"
int main() {
    std::string commands = "generator sphere 1 10 10 sphere.3d";
    GeometricFigure input = parseThreeCoordenateInput(commands);
    executeCommands(input);
    std::cout << "Graphic type: " << input.graphicType << '\n';
    std::cout << "radius_or_length: " << input.radius_or_length << '\n';
    std::cout << "slices_or_grid: " << input.slices_or_grid << '\n';
    std::cout << "Stacks: " << input.stacks << '\n';
    std::cout << "Output file: " << input.outputFile << '\n';
    return 0;
}
