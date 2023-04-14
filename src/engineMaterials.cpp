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

Content::Content() {};

void Content::insert_PUSH_MATRIX() {
    this->actions.push_back(AC_PUSH_MATRIX);
    cout << "added a push matrix!" << this->actions.size() << endl; 
}
void Content::insert_POP_MATRIX() {
    this->actions.push_back(AC_POP_MATRIX);
    cout << "added a pop matrix!" << this->actions.size() << endl;
}
void Content::insert_TRANSLATE(Point p) {
    this->actions.push_back(AC_TRANSLATE);
    this->arguments.push_back(p.x);
    this->arguments.push_back(p.y);
    this->arguments.push_back(p.z);
    cout << "added a translate!" << this->actions.size() << endl;
}
void Content::insert_ROTATE(float angle, Point p) {
    this->actions.push_back(AC_ROTATE);
    this->arguments.push_back(angle);
    this->arguments.push_back(p.x);
    this->arguments.push_back(p.y);
    this->arguments.push_back(p.z);
    cout << "added a rotate!" << this->actions.size() << endl;
}
void Content::insert_SCALE(Point p) {
    this->actions.push_back(AC_SCALE);
    this->arguments.push_back(p.x);
    this->arguments.push_back(p.y);
    this->arguments.push_back(p.z);
    cout << "added a scale!" << this->actions.size() << endl;

}
void Content::insert_MODEL(const string& filename) {
    this->actions.push_back(AC_MODEL);
    this->models.push_back(filename);
    cout << "added a model!" << this->actions.size() << endl;
}

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
            cout << "did a push matrix!" << endl;
        } else if (action == AC_POP_MATRIX) {
                glPopMatrix();
                cout << "did a pop matrix!" << endl;
        } else if (action == AC_TRANSLATE) {
            float x = this->arguments[i_arg];
            float y = this->arguments[i_arg+1];
            float z = this->arguments[i_arg+2];        
            glTranslatef(x, y, z);
            cout << "Translation of " << x << " " << y << " " << z << endl;
            i_arg += 3;
        } else if (action == AC_ROTATE) {       
            float angle = this->arguments[i_arg];
            float x = this->arguments[i_arg+1];
            float y = this->arguments[i_arg+2];
            float z = this->arguments[i_arg+3];   
            glRotatef(angle, x, y, z);
            cout << "Rotation of " << angle << " " << x << " " << y << " " << z << endl;
            i_arg += 4;
        } else if (action == AC_SCALE) {    
            float x = this->arguments[i_arg];
            float y = this->arguments[i_arg+1];
            float z = this->arguments[i_arg+2];   
            glScalef(x, y, z);
            cout << "Scale of " << x << " " << y << " " << z << endl;
            i_arg += 3;
        } else if (action == AC_MODEL) {
            GeometricShape::drawObject(GeometricShape::readFrom3DFile(this->models[i_model]));
            cout << "Modeled "<< this->models[i_model] << endl;
            i_model++;
        } else {
                throw "Invalid Action Value!!";
        }
    }
}
