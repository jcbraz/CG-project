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

using namespace std;

struct GeometricFigure {
    string graphicType;
    double radius_or_length;
    int slices_or_grid;
    int stacks;
    string outputFile;
};

GeometricFigure parseThreeCoordenateInput(string commands) {
    stringstream input(commands);
    string token;
    vector<string> tokens;
    while (input >> token) {
        tokens.push_back(token);
    }

    GeometricFigure input_struct;
    if (tokens.size() == 6) {
        input_struct.graphicType = tokens[1];
        input_struct.radius_or_length = stod(tokens[2]);
        input_struct.slices_or_grid = stoi(tokens[3]);
        input_struct.stacks = stoi(tokens[4]);
        input_struct.outputFile = tokens[5];
    } else if (tokens.size() == 5) {
        input_struct.graphicType = tokens[1];
        input_struct.radius_or_length = stod(tokens[2]);
        input_struct.slices_or_grid = stoi(tokens[3]);
        input_struct.stacks = -1;
        input_struct.outputFile = tokens[4];
    }
    return input_struct;
}

void executeCommands(GeometricFigure input_struct) {

    GLUquadric* quad = gluNewQuadric();
    if (input_struct.graphicType == "sphere") {
        glBegin(GL_TRIANGLES);
            gluSphere(quad,input_struct.radius_or_length, input_struct.slices_or_grid, input_struct.stacks);
        glEnd();
        gluDeleteQuadric(quad);
    } else if (input_struct.graphicType == "box") {
    } else if (input_struct.graphicType == "cone") {
    } else if (input_struct.graphicType == "plane") {
    } else {
        cout << "Invalid Graphic Type";
        
    }

    glFlush();
}


// Para executar, ir para a pasta build, "make group_project", "./group_project"
int main() {
    string commands = "generator sphere 1 10 10 sphere.3d";
    GeometricFigure input = parseThreeCoordenateInput(commands);
    executeCommands(input);
    cout << "Graphic type: " << input.graphicType << '\n';
    cout << "radius_or_length: " << input.radius_or_length << '\n';
    cout << "slices_or_grid: " << input.slices_or_grid << '\n';
    cout << "Stacks: " << input.stacks << '\n';
    cout << "Output file: " << input.outputFile << '\n';
    return 0;
}


// montar um constructor no World que recebe um World para conseguir aceder variaveis privadas