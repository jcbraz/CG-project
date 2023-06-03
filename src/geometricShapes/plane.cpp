#include "geometricShapes.h"

/*
 *
 * PLANE 
 *
 */

Plane::Plane() {
    Plane::length = 1.0f;
    Plane::divisions = 3;
    Plane::fileName = "plane.3d";
}

Plane::Plane(float length, int divisions) {
    Plane::length = length;
    Plane::divisions = divisions;
    Plane::fileName = "plane.3d";

}

Plane::Plane(float length, int divisions, string fileName) {
    this->length = length;
    this->divisions = divisions;
    this->fileName = std::move(fileName);

    vector<_3f> points;
    vector<_3f> normals;
    float n_d = (float) length / (float) divisions;
    float h_l = (float) length / 2;
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            // Calculate the vertices for the triangles
            _3f v1(-h_l + n_d * j, 0, -h_l + n_d * i);
            _3f v2(-h_l + n_d * j, 0, -h_l + n_d * (i + 1));
            _3f v3(-h_l + n_d * (j + 1), 0, -h_l + n_d * i);

            // Calculate the vertices for the second triangle
            _3f v4(-h_l + n_d * j, 0, -h_l + n_d * (i + 1));
            _3f v5(-h_l + n_d * (j + 1), 0, -h_l + n_d * (i + 1));
            _3f v6(-h_l + n_d * (j + 1), 0, -h_l + n_d * i);

            // Calculate the normal for the second triangle (v4, v5, v6)

            // Add the normals for the two triangles
            normals.push_back(_3f(0, 1, 0));
            normals.push_back(_3f(0, 1, 0));
            normals.push_back(_3f(0, 1, 0));
            normals.push_back(_3f(0, 1, 0));
            normals.push_back(_3f(0, 1, 0));
            normals.push_back(_3f(0, 1, 0));

            // Add the vertices for the two triangles
            points.push_back(v1);
            points.push_back(v2);
            points.push_back(v3);
            points.push_back(v4);
            points.push_back(v5);
            points.push_back(v6);
        }
    }

    this->points.push_back(GSPoints(GL_TRIANGLES, points, normals));
}

void Plane::Print(ostream &) const {
    cout << "Geometric Shape:Plane" << endl;
    cout << "Length:" << Plane::length << endl;
    cout << "Divisions:" << Plane::divisions << endl;
}
