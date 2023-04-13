#include <vector>
#include <chrono>
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
#include "engineMaterials.h"

using namespace std;

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
void * applyTranslation(Point p) {
    glTranslatef(p.x, p.y, p.z);
}

void applyScale(Point p) {
    glScalef(p.x, p.y, p.z);
}

void applyRotation(float angle, Point p) {
    glRotatef(angle, p.x, p.y, p.z);
}

// Models
void * drawModel(vector<Point> pts) {
    cout << "boas" << endl;
}

/*
void EngineMaterials::displayFPS () {
    static int framecount = 0;
    static auto start = std::chrono::high_resolution_clock::now();

    framecount ++;

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

    //dar update dos frames a cada segundo (definido como 1000 milissegundos)

    if (elapsed >1000){
        float fps=framecount / (elapsed/1000.0f);
        framecount=0;
        start=end;
        std::cout << "FPS: " << fps << std::endl;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutSwapBuffers();
}
*/