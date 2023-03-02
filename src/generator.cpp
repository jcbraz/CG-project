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


using namespace std;

enum GeometricType {NONE=-1, PLANE, BOX, SPHERE, CONE};

ostream& operator << (ostream& strm, GeometricType& gt) {
	const string name_gt[] = {"NaN", "Plane", "Box", "Sphere", "Cone"};
	return strm << name_gt[gt+1];
} 

struct GeometricFigure {
	GeometricType geometric_type;
	vector<int> values;
	double radius;

	public:
	GeometricFigure() {
		geometric_type = NONE;
		radius = 0.0;
	}
	
	friend ostream& operator << (ostream& strm, GeometricFigure * gf) {
		strm << "Geometric Figure: " << gf->geometric_type << endl;
		if (gf->radius != 0.0)
			strm << "Input Value:" << gf->radius << endl;
		for (int i = gf->values.size()-1; i >= 0; i--)
			strm << "Input Value:" << gf->values[i] << endl;
		return strm;
	}
};

GeometricType getGeometricType(string text) {
	if (!text.compare("plane.3d")) return PLANE;
	else if (!text.compare("box.3d")) return BOX;
	else if (!text.compare("sphere.3d")) return SPHERE;
	else if (!text.compare("cone.3d")) return CONE;
	throw invalid_argument("Invalid Geometric Figure!");
}

void parseValues(GeometricFigure * gf, size_t n, char ** values) {
	try {
		gf->values.push_back(stoi(values[n--]));
		gf->values.push_back(stoi(values[n--]));
		if (gf->geometric_type == CONE) 
			gf->values.push_back(stoi(values[n--]));
		if (gf->geometric_type == SPHERE || gf->geometric_type == CONE)
			gf->radius = stod(values[n]);	
	} catch (exception& ex) {
		throw invalid_argument("Invalid Input Values!");
	}
}

/*
void executeCommands(GeometricFigure input_struct) {

    GLUquadric* quad = gluNewQuadric();
    if (input_struct.graphicType == "sphere") {
        gluSphere(quad,input_struct.radius_or_length, input_struct.slices_or_grid, input_struct.stacks);
        gluDeleteQuadric(quad);
    } else if (input_struct.graphicType == "box") {
    } else if (input_struct.graphicType == "cone") {
    } else if (input_struct.graphicType == "plane") {
    } else {
        cout << "Invalid Graphic Type";
    }

    glFlush();
}

*/

// Para executar, ir para a pasta build, "make group_project", "./group_project"
int main(int argc, char ** argv) {

	GeometricFigure * gf = new GeometricFigure;
	
	try {
		gf->geometric_type = getGeometricType(argv[argc-1]);
		parseValues(gf, argc-2, argv);
	}
	catch (exception &ex) {
		cout << ex.what() << endl;
		exit(0);
	}
	
	cout << "GF: " << gf << endl;
	//executeCommands(...);
    return 0;
}
