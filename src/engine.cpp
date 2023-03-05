//
// Created by user13 on 04-03-2023.
//
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
    GeometricShape * cone = new Cone(2, 3, 3, 1);
    vector<Point> pointss = cone->getPoints();
    GeometricShape::writeTo3DFile(pointss, "cone.3d");
    vector<Point> points = GeometricShape::readFrom3DFile(cone->getFileName());
    GeometricShape::drawObject(points);

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

void createGeometricShape() {
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

    createGeometricShape();

    return 0;
}
