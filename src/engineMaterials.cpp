#include <vector>
#include "engineMaterials.h"

#include <iostream>
#include <string>
#include <vector>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define GLUT_
#include "geometricShapes.h"

using namespace std;


Point::Point(float x, float y, float z) : x(x), y(y), z(z) {};

Window::Window(float w, float h) : width(w), height(h) {};

Camera::Camera(Point position, Point lookAt, Point up, Point projection) :
 position(position),
 lookAt(lookAt),
 up(up),
 projection(projection) {};

World::World(Window w, Camera c) : window(w), camera(c) {}

// Groups
void enterGroup() {
    glPushMatrix();
}
void leaveGroup() {
    glPopMatrix();
}

// Transforms
void applyTranslation(Point p) {
    glTranslatef(p.x, p.y, p.z);
}

void applyScale(Point p) {
    glScalef(p.x, p.y, p.z);
}

void applyRotation(float angle, Point p) {
    glRotatef(angle, p.x, p.y, p.z);
}

// Models
void drawModel(vector<Point> pts);