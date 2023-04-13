#include <vector>
#include "engineMaterials.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define GLUT_

using namespace std;


Point::Point(float x, float y, float z) : x(x), y(y), z(z) {};

Window::Window(float w, float h) : width(w), height(h) {};

Camera::Camera(Point position, Point lookAt, Point up, Point projection) :
 position(position),
 lookAt(lookAt),
 up(up),
 projection(projection) {};


// Groups
void enterGroup() {
    glPushMatrix();
}
void leaveGroup() {
    glPopMatrix();
}

// Transforms
void translate(Point p) {
    glTranslatef(p.x, p.y, p.z);
}
void scale(Point p) {
    glScalef(p.x, p.y, p.z);
}
void rotate(float angle, Point p) {
    glRotatef(angle, p.x, p.y, p.z);
}
// Models
void drawModel(vector<Point> pts);
