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
#include "parseXML.h"

using namespace std;

World * world;
vector<Point> points;
Camera c;
Position p;
LookAt la;
Up up;
Projection proj;

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
    gluPerspective(proj.fov ,ratio, proj.near ,proj.far);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();


    gluLookAt(p.x, p.y, p.z,
              la.x, la.y, la.z,
              up.x, up.y, up.z);

    //gluLookAt(0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1, 0);

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

    GeometricShape::drawObject(points);

    // End of frame
    glutSwapBuffers();
}

int is_skeleton = 0;
void processKeys(unsigned char key, int x, int y) {
    if (key == 'x') {
        if (is_skeleton)
            glPolygonMode(GL_FRONT, GL_FILL);
        else
            glPolygonMode(GL_FRONT, GL_LINE);
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
    //glutInitWindowSize(800, 800);
    glutInitWindowSize(world->getWidth(), world->getHeight());
    glutCreateWindow("Engine");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    //glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // Glut's main cycle
    glutMainLoop();

}



// Para executar, ir para a pasta build, "make group_project", "./group_project"
int main(int argc, char ** argv) {

    world = new World("../config/config.xml");
    vector<string> fic = world->getFiles();
    proj = world->getCamera().getProjection();


    c = world->getCamera();
    p = c.getPosition();
    la = c.getLookAt();
    up = c.getUp();

    for (auto elem : world->getFiles()) {
        vector<Point> tmp = GeometricShape::readFrom3DFile(elem);
        for (auto p: tmp) {
            points.push_back(p);
            cout << p.x << endl;
        }

    }

    createGeometricShape();

    return 0;
}

