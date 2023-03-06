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
#include <cstring>
#include <iomanip>

#define FLOAT_PRECISION 5

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
 * BOX CLASS
 *
 */

Box::Box() {
    Box::length = 1.0f;
    Box::divisions = 3;  // grid
}

Box::Box(float length, int divisions) {
    Box::length = length;
    Box::divisions = divisions;
    Box::fileName = "box.3d";
}

Box::Box(float length, int divisions, string pathFile) {
    Box::length = length;
    Box::divisions = divisions;
    Box::fileName = pathFile;
}

void Box::Print(ostream &) const {
    cout << "Geometric Shape: Box" << endl;
    cout << "Length" << Box::length << endl;
    cout << "Divisions" << Box::divisions << endl;
}

vector<Point> Box::getPoints() {
    vector<Point> points;
    float measure = length / 2.0f;
    float division_size = length / (float)divisions;

    // Front & Back

    for (int i = 0; i < divisions; i++) {
        float x = -measure + i * division_size;
        for (int j = 0; j < divisions; j++) {
            float y = -measure + j * division_size;
            points.push_back(Point(x, y, -measure));
            points.push_back(Point(x, y+division_size, -measure));
            points.push_back(Point(x+division_size, y, -measure));

            points.push_back(Point(x+division_size, y, -measure));
            points.push_back(Point(x, y+division_size, -measure));
            points.push_back(Point(x+division_size, y+division_size, -measure));


            points.push_back(Point(x, y, measure));
            points.push_back(Point(x+division_size, y, measure));
            points.push_back(Point(x, y+division_size, measure));

            points.push_back(Point(x+division_size, y, measure));
            points.push_back(Point(x+division_size, y+division_size, measure));
            points.push_back(Point(x, y+division_size, measure));

        }
    }


    // Top & Bottom
    for (int i = 0; i < divisions; i++) {
        float x = -measure + i * division_size;
        for (int j = 0; j < divisions; j++) {
            float z = -measure + j * division_size;


            // Top
            points.push_back(Point(x, measure, z));
            points.push_back(Point(x, measure, z+division_size));
            points.push_back(Point(x+division_size, measure, z));


            points.push_back(Point(x+division_size, measure, z));
            points.push_back(Point(x, measure, z+division_size));
            points.push_back(Point(x+division_size, measure, z+division_size));

            // Bottom
            points.push_back(Point(x, -measure, z));
            points.push_back(Point(x+division_size, -measure, z));
            points.push_back(Point(x, -measure, z+division_size));


            points.push_back(Point(x+division_size, -measure, z));
            points.push_back(Point(x+division_size, -measure, z+division_size));
            points.push_back(Point(x, -measure, z+division_size));

        }
    }
    

    // Right & Left
    for (int i = 0; i < divisions; i++) {
        float y = -measure + i * division_size;
        for (int j = 0; j < divisions; j++) {
            float z = -measure + j * division_size;
            points.push_back(Point(-measure, y, z));
            points.push_back(Point(-measure, y, z+division_size));
            points.push_back(Point(-measure, y+division_size, z));


            points.push_back(Point(-measure, y+division_size, z));
            points.push_back(Point(-measure, y, z+division_size));
            points.push_back(Point(-measure, y+division_size, z+division_size));


            points.push_back(Point(measure, y, z));
            points.push_back(Point(measure, y+division_size, z));
            points.push_back(Point(measure, y, z+division_size));


            points.push_back(Point(measure, y+division_size, z));
            points.push_back(Point(measure, y+division_size, z+division_size));
            points.push_back(Point(measure, y, z+division_size));

        }
    }


    return points;
}

/*
 *
 * END BOX CLASS
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

void GeometricShape::writeTo3DFile(vector<Point> points, string fName) {
    ofstream file(fName);
    cout << "Writing Points to:" << fName << endl;
    for (auto p : points) {
        file << setprecision(FLOAT_PRECISION) << p.x << " " << p.y << " " << p.z << " ";
    }
    file << endl;
    file.close();
}

vector<Point> GeometricShape::readFrom3DFile(string fName) {
    ifstream file(fName);
    string line;
    cout << "Reading From:" << fName << endl;
    getline(file, line);

    vector<Point> points;
    vector<float> nms;
    char buf[32];
    int j = 0;
    for (int i = 0; i < line.length(); i++) {

        if (isdigit(line[i]) || line[i] == '.' || line[i] == '-' || line[i] == 'e') {
            buf[j++] = line[i];
        }
        else {
            nms.push_back(stof(buf));
            memset(buf, 0, 32);
            j = 0;
        }
        if (nms.size() == 3) {
            points.push_back(Point(nms[0], nms[1], nms[2]));
            nms.clear();
        }
    }
    return points;
}
