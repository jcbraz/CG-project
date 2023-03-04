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

#define STACKS 0
#define DIMENSION 1
#define DIVISION_EDGE 0
#define SLICES 1
#define HEIGHT 2

#include "geometricShapes.h"

using namespace std;

// Para executar, ir para a pasta build, "make group_project", "./group_project"
int main(int argc, char ** argv) {

    GeometricShape * gShape;

    try {
        string s_gShape = argv[1];
        //if (s_gShape == "plane.3d")
            //gShape = new Plane(stof(argv[1]), stoi(argv[2]));
            //    else if (s_gShape == "box.3d")
            //        gShape = new Box(stof(argv[1]), stoi(argv[2]));
        if (s_gShape == "cone")
            gShape = new Cone(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]), argv[6]);
            //    else if (s_gShape == "sphere.3d")
            //        gShape = new Sphere(stof(argv[1]), stoi(argv[2]), stoi(argv[3]));
        else
            throw invalid_argument("Invalid Shape!");
    } catch (exception& ex) {
        cerr << "Error Initializing:" << ex.what() << endl;
        exit(0);
    }

    cout << *gShape << endl;
    gShape->writeTo3DFile(gShape->getPoints());
	//executeCommands(...);
    return 0;
}
