#include "geometricShapes.h"

/*
 *
 * SPHERE CLASS
 *
 */

Sphere::Sphere(float radius, int slices, int stacks, string fileName) {
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
    this->fileName = std::move(fileName);

    vector<_3f> points;
    vector<_3f> normals;
    vector<_3f> texCoords;

    float _alpha = 2 * M_PI / slices;
    float _beta = M_PI / stacks;
    float r = radius;
    for (int j = 0; j < stacks; j++) {
        float bv = -M_PI/2 + j * _beta;
        float bhv = bv + _beta;

        for (int i = 0; i < slices; i++) {
            float av = i * _alpha;
            float ahv = av + _alpha;

            // Calculate texture coordinates
            float u = static_cast<float>(i) / static_cast<float>(slices);
            float v = static_cast<float>(j) / static_cast<float>(stacks);

            texCoords.push_back(_3f(u, v, 0.0f));
            texCoords.push_back(_3f(u + (1.0f / slices), v, 0.0f));
            texCoords.push_back(_3f(u + (1.0f / slices), v + (1.0f / stacks), 0.0f));
            
            texCoords.push_back(_3f(u, v, 0.0f));
            texCoords.push_back(_3f(u + (1.0f / slices), v + (1.0f / stacks), 0.0f));
            texCoords.push_back(_3f(u, v + (1.0f / stacks), 0.0f));


            points.push_back(_3f(r * cos(bv) * sin(av), r * sin(bv) ,r * cos(bv) * cos(av)));
            points.push_back(_3f(r * cos(bv) * sin(ahv), r * sin(bv) ,r * cos(bv) * cos(ahv)));
            points.push_back(_3f(r * cos(bhv) * sin(ahv), r * sin(bhv) ,r * cos(bhv) * cos(ahv)));
            
            normals.push_back(_3f(r * cos(bv) * sin(av), r * sin(bv) ,r * cos(bv) * cos(av)));
            normals.push_back(_3f(r * cos(bv) * sin(av), r * sin(bv) ,r * cos(bv) * cos(av)));  
            normals.push_back(_3f(r * cos(bhv) * sin(ahv), r * sin(bhv) ,r * cos(bhv) * cos(ahv)));

            points.push_back(_3f(r * cos(bv) * sin(av), r * sin(bv) ,r * cos(bv) * cos(av)));
            points.push_back(_3f(r * cos(bhv) * sin(ahv), r * sin(bhv) ,r * cos(bhv) * cos(ahv)));
            points.push_back(_3f(r * cos(bhv) * sin(av), r * sin(bhv) ,r * cos(bhv) * cos(av)));

            normals.push_back(_3f(r * cos(bv) * sin(av), r * sin(bv) ,r * cos(bv) * cos(av)));
            normals.push_back(_3f(r * cos(bhv) * sin(ahv), r * sin(bhv) ,r * cos(bhv) * cos(ahv)));
            normals.push_back(_3f(r * cos(bhv) * sin(av), r * sin(bhv) ,r * cos(bhv) * cos(av)));
        }
    }

    this->points.push_back(GSPoints(GL_TRIANGLES, points, normals, texCoords));
}

void Sphere::Print(ostream &) const {
    cout << "Geometric Shape: Sphere" << endl;
    cout << "Radius:" << Sphere::radius << endl;
    cout << "Slices:" << Sphere::slices << endl;
    cout << "Stacks:" << Sphere::stacks << endl;
}
