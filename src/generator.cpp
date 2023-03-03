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

#define _USE_MATH_DEFINES
#include <math.h>

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
	float radius;

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
			gf->radius = stof(values[n]);	
	} catch (exception& ex) {
		throw invalid_argument("Invalid Input Values!");
	}
}

struct Point {
    float x, y, z;

    public:
    Point(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

void drawCone(float radius, int height, int slices, int stacks) {

    float alpha = 2 * M_PI / slices;

    Point * p = new Point(0, 0, radius);

    glBegin(GL_TRIANGLES);
        for (int i = 0; i < slices; i++) {
            glColor3f(1.0f, 1.0f, 1.0f);
			
			Point * p_1 = new Point(
					radius * sin(alpha * i),
					0,
					radius * cos(alpha * i)
					);

			Point * h = new Point(0, height, 0);
			
			Point * v_1 = new Point(
					h->x - p_1->x,
					h->y - p_1->y,
					h->z - p_1->z
					);
			
			Point * p_2 = new Point(
					radius * sin(alpha * (i+1)),
					0,
					radius * cos(alpha * (i+1))
					);
			
			Point * v_2 = new Point(
					h->x - p_2->x,
					h->y - p_2->y,
					h->z - p_2->z
					);
			
            // Cone Base
            glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(p_2->x, p_2->y, p_2->z);
			glVertex3f(p_1->x, p_1->y, p_1->z);

			for (int j = 0; j < stacks; j++) {

				// Stack Bottom Triangle
				glColor3f(0.5f, 0.5f, 0.0f);
				glVertex3f(
						p_1->x + j*v_1->x/stacks,
					   	p_1->y + j*v_1->y/stacks,
					   	p_1->z + j*v_1->z/stacks);
				
				glVertex3f(
						p_2->x + (j+1)*v_2->x/stacks,
					   	p_2->y + (j+1)*v_2->y/stacks, 
						p_2->z + (j+1)*v_2->z/stacks);
				
				glVertex3f(p_2->x + j*v_2->x/stacks,
					   	p_2->y + j*v_2->y/stacks,
					   	p_2->z + j*v_2->z/stacks);
			
				// Stack Top Triangle
				glVertex3f(
						p_1->x + j*v_1->x/stacks,
					   	p_1->y + j*v_1->y/stacks,
					   	p_1->z + j*v_1->z/stacks);
				
				glVertex3f(
						p_1->x + (j+1)*v_1->x/stacks,
					   	p_1->y + (j+1)*v_1->y/stacks, 
						p_1->z + (j+1)*v_1->z/stacks);
				
				glVertex3f(
						p_2->x + (j+1)*v_2->x/stacks,
					   	p_2->y + (j+1)*v_2->y/stacks, 
						p_2->z + (j+1)*v_2->z/stacks);
			}
			delete p_1, p_2, h, v_1, v_2;
        }
    glEnd();

}


void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio 
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(5.0f, 5.0f, 5.0f,
              0.0,0.0,0.0,
              0.0f,1.0f,0.0f);

    glBegin(GL_LINES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-100.0f, 0.0f, 0.0f);
        glVertex3f(100.0f, 0.0f, 0.0f);

        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(0.0f, -100.0f, 0.0f);
        glVertex3f(0.0f, 100.0f, 0.0f);

        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 0.0f, -100.0f);
        glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

	// Draw Geometric Figure
    //drawCylinder(1,2,320);
	drawCone(2, 3, 100, 20);
    // End of frame
    glutSwapBuffers();
}

int is_skeleton = 0;
void processKeys(unsigned char key, int x, int y) {
	if (key == 'x') {
		if (is_skeleton)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		is_skeleton = !is_skeleton;
		cout << "Pressed: " << key << endl;
	}

	glutPostRedisplay();
}

void createGeometricFigure(GeometricFigure * gf) {
	// init glut and window
	int f = 1;
	char * s[1] = {" "};
	glutInit(&f, s);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Generator");

	// Required callback registry 
		glutDisplayFunc(renderScene);
		glutReshapeFunc(changeSize);
		
	// Callback registration for keyboard processing
		glutKeyboardFunc(processKeys);
		//glutSpecialFunc(processSpecialKeys);

	//  OpenGL settings
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BACK);

	// Glut's main cycle
	glutMainLoop();
	
}

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

	createGeometricFigure(gf);

	delete gf;
	//executeCommands(...);
    return 0;
}
