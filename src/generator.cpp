#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "geometricShapes/geometricShapes.h"

using namespace std;

// Para executar, ir para a pasta build, "make group_project", "./group_project"
int main(int argc, char ** argv) {

    GeometricShape * gShape;

    try {
        string s_gShape = argv[1];
        if (s_gShape == "plane")
            gShape = new Plane(stof(argv[2]), stoi(argv[3]), argv[4]);
        else if (s_gShape == "box")
            gShape = new Box(stof(argv[2]), stoi(argv[3]), argv[4]);
        else if (s_gShape == "cone")
            gShape = new Cone(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]), argv[6]);
        else if (s_gShape == "sphere")
            gShape = new Sphere(stof(argv[2]), stoi(argv[3]), stoi(argv[4]), argv[5]);
        else if (s_gShape =="ring")
            gShape = new Ring(stof(argv[2]), stof(argv[3]), stoi(argv[4]), stoi(argv[5]), argv[6]);
        else if (s_gShape == "patch") {
            vector<GSPoints> gspoints = GeometricShape::readFromBezierPatchFile(argv[2], stoi(argv[3]));
            GeometricShape::writeTo3DFile(gspoints, argv[4]);
            return 0;
        }
        else
            throw invalid_argument("Invalid Shape!");
    } catch (exception& ex) {
        cerr << "Error Initializing:" << ex.what() << endl;
        exit(0);
    }

    cout << *gShape << endl;
    gShape->writeTo3DFile(gShape->getPoints(), gShape->getFileName());

    return 0;
}
