#include <math.h>

#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#define GLUT_
#include "engineMaterials.h"
#include "geometricShapes.h"

using namespace std;

Window::Window(float w, float h) : width(w), height(h){};

Camera::Camera(Point position, Point lookAt, Point up, Point projection)
    : position(position), lookAt(lookAt), up(up), projection(projection){};

World::World(Window w, Camera c) : window(w), camera(c) {}

Content::Content(){};

void Content::insert_PUSH_MATRIX() { this->actions.push_back(AC_PUSH_MATRIX); }
void Content::insert_POP_MATRIX() { this->actions.push_back(AC_POP_MATRIX); }
void Content::insert_TRANSLATE(Point p) {
    this->actions.push_back(AC_TRANSLATE);
    this->arguments.push_back(p.x);
    this->arguments.push_back(p.y);
    this->arguments.push_back(p.z);
}
void Content::insert_ROTATE(float angle, Point p) {
    this->actions.push_back(AC_ROTATE);
    this->arguments.push_back(angle);
    this->arguments.push_back(p.x);
    this->arguments.push_back(p.y);
    this->arguments.push_back(p.z);
}
void Content::insert_SCALE(Point p) {
    this->actions.push_back(AC_SCALE);
    this->arguments.push_back(p.x);
    this->arguments.push_back(p.y);
    this->arguments.push_back(p.z);
}
void Content::insert_MODEL(const string& filepath) {
    this->actions.push_back(AC_MODEL);
    this->i_models.push_back(filepath);
    if (this->models.find(filepath) == this->models.end())
        this->models[filepath] = GeometricShape::readFrom3DFile(filepath);
}

void Content::insert_COLOR(Point p) {
    this->actions.push_back(AC_COLOR);
    this->arguments.push_back(p.x);
    this->arguments.push_back(p.y);
    this->arguments.push_back(p.z);
}

void Content::insert_3D_CIRC_RAND_OBJ_PLACEMENT(float radius,
                                                bool isRandRotation, int n,
                                                Point scale,
                                                const string& filepath) {
    for (int i = 0; i < n; i++) {
        float px = 0, pz = 0;
        while (pow(px, 2) + pow(pz, 2) < pow(radius, 2)) {
            float angle = 2.0 * M_PI * ((float)rand() / RAND_MAX);

            px = radius * cos(angle);
            pz = radius * sin(angle);
        }
        this->insert_PUSH_MATRIX();
        this->insert_TRANSLATE(Point(px, 0, pz));
        if (isRandRotation) {
            float r_angle = 360.0 * ((double)rand() / RAND_MAX);
            this->insert_ROTATE(r_angle, Point(0, 1, 1));
        }

        if (scale.x != 1 || scale.y != 1 || scale.z != 1) {
            this->insert_SCALE(scale);
        }

        this->insert_MODEL(filepath);
        this->insert_POP_MATRIX();
    }
}

void Content::insert_DISABLE_CULL() {
    this->actions.push_back(AC_DISABLE_CULL);
}

void Content::insert_ENABLE_CULL() { this->actions.push_back(AC_ENABLE_CULL); }

void Content::applyContent() {
    int i_arg = 0;
    int i_model = 0;

    if (this->actions.empty()) {
        cout << "No content!" << endl;
        return;
    }

    for (int action : this->actions) {
        if (action == AC_PUSH_MATRIX) {
            glPushMatrix();
        } else if (action == AC_POP_MATRIX) {
            glPopMatrix();
        } else if (action == AC_TRANSLATE) {
            float x = this->arguments[i_arg];
            float y = this->arguments[i_arg + 1];
            float z = this->arguments[i_arg + 2];
            glTranslatef(x, y, z);
            i_arg += 3;
        } else if (action == AC_ROTATE) {
            float angle = this->arguments[i_arg];
            float x = this->arguments[i_arg + 1];
            float y = this->arguments[i_arg + 2];
            float z = this->arguments[i_arg + 3];
            glRotatef(angle, x, y, z);
            i_arg += 4;
        } else if (action == AC_SCALE) {
            float x = this->arguments[i_arg];
            float y = this->arguments[i_arg + 1];
            float z = this->arguments[i_arg + 2];
            glScalef(x, y, z);
            i_arg += 3;
        } else if (action == AC_MODEL) {
            GeometricShape::drawObject(this->models[this->i_models[i_model]]);
            i_model++;
        } else if (action == AC_COLOR) {
            float r = this->arguments[i_arg];
            float g = this->arguments[i_arg + 1];
            float b = this->arguments[i_arg + 2];
            glColor3f(r, g, b);
            i_arg += 3;
        } else if (action == AC_DISABLE_CULL) {
            glDisable(GL_CULL_FACE);
        } else if (action == AC_ENABLE_CULL) {
            glEnable(GL_CULL_FACE);
        } else {
            throw "Invalid Action Value!!";
        }
    }
}
