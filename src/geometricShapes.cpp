//
// Created by user13 on 03-03-2023.
//

#include <iostream>
#include <sstream>
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
 * END POINT STRUCT
 *
 */


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
}

void Cone::drawObject() {

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
    }
    glEnd();

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

void Plane::drawObject() {

}

void Plane::Print(ostream &) const {
    cout << "Geometric Shape:Plane" << endl;
    cout << "Length:" << Plane::length << endl;
    cout << "Divisions:" << Plane::divisions << endl;
}

