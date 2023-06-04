#include "geometricShapes.h"

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
    Cone::fileName = std::move(pathFile);

    vector<_3f> points;

    float alpha = 2 * M_PI / slices;
    float v_h = height / stacks;
    float v_r = radius / stacks;
    // Base
    for (int i = 0; i < slices; i++) {
        points.push_back(_3f(0, 0, 0));
        points.push_back(_3f(radius * sin(alpha * (i + 1)), 0, radius * cos(alpha * (i + 1))));
        points.push_back(_3f(radius * sin(alpha * i), 0, radius * cos(alpha * i)));

        for (int j = 0; j < stacks-1; j++) {

            points.push_back(_3f((radius - v_r * j) * sin(alpha * i), j * v_h,(radius - v_r * j) * cos(alpha * i)));
            points.push_back(_3f((radius - v_r * j) * sin(alpha * (i+1)), j * v_h, (radius - v_r * j) * cos(alpha * (i+1))));
            points.push_back(_3f((radius - v_r * (j+1)) * sin(alpha * (i+1)), (j+1) * v_h, (radius - v_r * (j+1)) * cos(alpha * (i+1))));

            points.push_back(_3f((radius - v_r * j) * sin (alpha * i), j * v_h, (radius - v_r * j) * cos(alpha * i)));
            points.push_back(_3f((radius - v_r * (j+1)) * sin (alpha * (i+1)), (j+1) * v_h, (radius - v_r * (j+1)) * cos(alpha * (i+1))));
            points.push_back(_3f((radius - v_r * (j+1)) * sin (alpha * i), (j+1) * v_h, (radius - v_r * (j+1)) * cos(alpha * i)));

        }
    }

    for (int i = 0; i < slices; i++) {
        points.push_back(_3f((radius - v_r * (stacks-1)) * sin(alpha * i), (stacks-1) * v_h,(radius - v_r * (stacks-1)) * cos(alpha * i)));
        points.push_back(_3f((radius - v_r * (stacks-1)) * sin(alpha * (i+1)), (stacks-1) * v_h, (radius - v_r * (stacks-1)) * cos(alpha * (i+1))));
        points.push_back(_3f((radius - v_r * stacks) * sin(alpha * (i+1)), stacks * v_h, (radius - v_r * stacks) * cos(alpha * (i+1))));
    }

    this->points.push_back(GSPoints(GL_TRIANGLES, points));
}

void Cone::Print(ostream &) const {
    cout << "Geometric Shape:Cone" << endl;
    cout << "Radius:" << Cone::radius << endl;
    cout << "Stacks:" << Cone::stacks << endl;
    cout << "Height:" << Cone::height << endl;
    cout << "Slices:" << Cone::slices << endl;

}