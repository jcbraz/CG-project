//
// Created by user13 on 03-03-2023.
//

#include <iostream>
#include <string>
#include <vector>

#include "geometricShapes.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define GLUT_

#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>

/*
 *
 * POINT STRUCT
 *
 */

Point::Point(float x, float y, float z) {
    Point::x = x;
    Point::y = y;
    Point::z = z;
}

Point::Point() {
    Point::x = 0;
    Point::y = 0;
    Point::z = 0;
}

/*
 *
 * CONE CLASS
 *
 */

Cone::Cone() {
    Cone::radius = 1;
    Cone::height = 1;
    Cone::slices = 3;
    Cone::stacks = 1;
}

Cone::Cone(float radius, float height, int slices, int stacks) {
    Cone::radius = radius;
    Cone::height = height;
    Cone::slices = slices;
    Cone::stacks = stacks;
    Cone::fileName = "cone.3d";
}

Cone::Cone(float radius, float height, int slices, int stacks, string pathFile) {
    Cone::radius = radius;
    Cone::height = height;
    Cone::slices = slices;
    Cone::stacks = stacks;
    Cone::fileName = pathFile;
}


vector<Point> Cone::getPoints() {
    vector<Point> points;

    float alpha = 2 * M_PI / slices;
    float v_h = height / stacks;
    float v_r = radius / stacks;
    // Base
    for (int i = 0; i < slices; i++) {
        points.push_back(Point(0, 0, 0));
        points.push_back(Point(radius * sin(alpha * i), 0, radius * cos(alpha * i)));
        points.push_back(Point(radius * sin(alpha * (i + 1)), 0, radius * cos(alpha * (i + 1))));

        for (int j = 0; j < stacks-1; j++) {

            points.push_back(Point((radius - v_r * j) * sin(alpha * i), j * v_h,(radius - v_r * j) * cos(alpha * i)));
            points.push_back(Point((radius - v_r * (j+1)) * sin(alpha * (i+1)), (j+1) * v_h, (radius - v_r * (j+1)) * cos(alpha * (i+1))));
            points.push_back(Point((radius - v_r * j) * sin(alpha * (i+1)), j * v_h, (radius - v_r * j) * cos(alpha * (i+1))));

            points.push_back(Point((radius - v_r * j) * sin (alpha * i), j * v_h, (radius - v_r * j) * cos(alpha * i)));
            points.push_back(Point((radius - v_r * (j+1)) * sin (alpha * i), (j+1) * v_h, (radius - v_r * (j+1)) * cos(alpha * i)));
            points.push_back(Point((radius - v_r * (j+1)) * sin (alpha * (i+1)), (j+1) * v_h, (radius - v_r * (j+1)) * cos(alpha * (i+1))));

        }
    }

    for (int i = 0; i < slices; i++) {
        points.push_back(Point((radius - v_r * (stacks-1)) * sin(alpha * i), (stacks-1) * v_h,(radius - v_r * (stacks-1)) * cos(alpha * i)));
        points.push_back(Point((radius - v_r * stacks) * sin(alpha * (i+1)), stacks * v_h, (radius - v_r * stacks) * cos(alpha * (i+1))));
        points.push_back(Point((radius - v_r * (stacks-1)) * sin(alpha * (i+1)), (stacks-1) * v_h, (radius - v_r * (stacks-1)) * cos(alpha * (i+1))));
    }

    return points;
}

void Cone::Print(ostream &) const {
    cout << "Geometric Shape:Cone" << endl;
    cout << "Radius:" << Cone::radius << endl;
    cout << "Stacks:" << Cone::stacks << endl;
    cout << "Height:" << Cone::height << endl;
    cout << "Slices:" << Cone::slices << endl;

}


/*
 *
 * END CONE CLASS
 *
 */

Plane::Plane() {
    Plane::length = 1.0f;
    Plane::divisions = 3;
}

Plane::Plane(float length, int divisions) {
    Plane::length = length;
    Plane::divisions = divisions;
}

void Plane::Print(ostream &) const {
    cout << "Geometric Shape:Plane" << endl;
    cout << "Length:" << Plane::length << endl;
    cout << "Divisions:" << Plane::divisions << endl;
}

/*
 *
 * END POINT STRUCT
 *
 */
void GeometricShape::drawObject(vector<Point> points) {
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 1.0f, 1.0f);
        for (auto p : points)
            glVertex3f(p.x, p.y, p.z);
    glEnd();
}

void GeometricShape::writeTo3DFile(vector<Point> points) {
    ofstream file(fileName);
    cout << "Writing Points to:" << fileName << endl;
    for (auto p : points) {
        file << p.x << " " << p.y << " " << p.z << " ";
    }
    file.close();
}
