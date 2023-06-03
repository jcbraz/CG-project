#include "geometricShapes.h"

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
    this->length = length;
    this->divisions = divisions;
    this->fileName = std::move(pathFile);

    vector<_3f> points;
    vector<_3f> normals;
    float measure = length / 2.0f;
    float division_size = length / (float)divisions;

    // Front & Back

    for (int i = 0; i < divisions; i++) {
        float x = -measure + i * division_size;
        for (int j = 0; j < divisions; j++) {
            float y = -measure + j * division_size;
            points.push_back(_3f(x, y, -measure));
            points.push_back(_3f(x, y+division_size, -measure));
            points.push_back(_3f(x+division_size, y, -measure));

            normals.push_back(_3f(0, 0, -1));
            normals.push_back(_3f(0, 0, -1));
            normals.push_back(_3f(0, 0, -1));

            points.push_back(_3f(x+division_size, y, -measure));
            points.push_back(_3f(x, y+division_size, -measure));
            points.push_back(_3f(x+division_size, y+division_size, -measure));

            normals.push_back(_3f(0, 0, -1));
            normals.push_back(_3f(0, 0, -1));
            normals.push_back(_3f(0, 0, -1));
            
            points.push_back(_3f(x, y, measure));
            points.push_back(_3f(x+division_size, y, measure));
            points.push_back(_3f(x, y+division_size, measure));

            normals.push_back(_3f(0, 0, 1));
            normals.push_back(_3f(0, 0, 1));
            normals.push_back(_3f(0, 0, 1));

            points.push_back(_3f(x+division_size, y, measure));
            points.push_back(_3f(x+division_size, y+division_size, measure));
            points.push_back(_3f(x, y+division_size, measure));

            normals.push_back(_3f(0, 0, 1));
            normals.push_back(_3f(0, 0, 1));
            normals.push_back(_3f(0, 0, 1));
        }
    }


    // Top & Bottom
    for (int i = 0; i < divisions; i++) {
        float x = -measure + i * division_size;
        for (int j = 0; j < divisions; j++) {
            float z = -measure + j * division_size;


            // Top
            points.push_back(_3f(x, measure, z));
            points.push_back(_3f(x, measure, z+division_size));
            points.push_back(_3f(x+division_size, measure, z));

            normals.push_back(_3f(0, 1, 0));
            normals.push_back(_3f(0, 1, 0));
            normals.push_back(_3f(0, 1, 0));            

            points.push_back(_3f(x+division_size, measure, z));
            points.push_back(_3f(x, measure, z+division_size));
            points.push_back(_3f(x+division_size, measure, z+division_size));

            normals.push_back(_3f(0, 1, 0));
            normals.push_back(_3f(0, 1, 0));
            normals.push_back(_3f(0, 1, 0));

            // Bottom
            points.push_back(_3f(x, -measure, z));
            points.push_back(_3f(x+division_size, -measure, z));
            points.push_back(_3f(x, -measure, z+division_size));

            normals.push_back(_3f(0, -1, 0));
            normals.push_back(_3f(0, -1, 0));
            normals.push_back(_3f(0, -1, 0));

            points.push_back(_3f(x+division_size, -measure, z));
            points.push_back(_3f(x+division_size, -measure, z+division_size));
            points.push_back(_3f(x, -measure, z+division_size));

            normals.push_back(_3f(0, -1, 0));
            normals.push_back(_3f(0, -1, 0));
            normals.push_back(_3f(0, -1, 0));

        }
    }


    // Right & Left
    for (int i = 0; i < divisions; i++) {
        float y = -measure + i * division_size;
        for (int j = 0; j < divisions; j++) {
            float z = -measure + j * division_size;
            points.push_back(_3f(-measure, y, z));
            points.push_back(_3f(-measure, y, z+division_size));
            points.push_back(_3f(-measure, y+division_size, z));

            normals.push_back(_3f(-1, 0, 0));
            normals.push_back(_3f(-1, 0, 0));
            normals.push_back(_3f(-1, 0, 0));

            points.push_back(_3f(-measure, y+division_size, z));
            points.push_back(_3f(-measure, y, z+division_size));
            points.push_back(_3f(-measure, y+division_size, z+division_size));

            normals.push_back(_3f(-1, 0, 0));
            normals.push_back(_3f(-1, 0, 0));
            normals.push_back(_3f(-1, 0, 0));

            points.push_back(_3f(measure, y, z));
            points.push_back(_3f(measure, y+division_size, z));
            points.push_back(_3f(measure, y, z+division_size));

            normals.push_back(_3f(-1, 0, 0));
            normals.push_back(_3f(-1, 0, 0));
            normals.push_back(_3f(-1, 0, 0));

            points.push_back(_3f(measure, y+division_size, z));
            points.push_back(_3f(measure, y+division_size, z+division_size));
            points.push_back(_3f(measure, y, z+division_size));

            normals.push_back(_3f(-1, 0, 0));
            normals.push_back(_3f(-1, 0, 0));
            normals.push_back(_3f(-1, 0, 0));

        }
    }


    this->points.push_back(GSPoints(GL_TRIANGLES, points,  normals));
}


void Box::Print(ostream &) const {
    cout << "Geometric Shape: Box" << endl;
    cout << "Length:" << Box::length << endl;
    cout << "Divisions:" << Box::divisions << endl;
}