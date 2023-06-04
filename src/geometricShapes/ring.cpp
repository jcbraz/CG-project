#include "geometricShapes.h"

/*
 *
 * RING CLASS
 *
 */

Ring::Ring(float innerRadius, float outerRadius, int slices, int segments, string fName) :
 innerRadius(innerRadius),
 outerRadius(outerRadius),
 slices(slices),
 segments(segments)
{
    this->fileName = fName;

    vector<_3f> points;
    float _alpha = 2 * M_PI / slices;
    float seg_size = (outerRadius - innerRadius) / segments;
    
    for (int i = 0; i < segments; i++) {
        
        float r1 = innerRadius + i * seg_size;
        float r2 = r1 + seg_size;

        for (int j = 0; j < slices; j++) {
            
            float a1 = _alpha * j;
            float a2 = a1 + _alpha;

                points.push_back(_3f(r1 * cos(a1) , 0, r1 * sin(a1)));
                points.push_back(_3f(r1 * cos(a2) , 0, r1 * sin(a2)));
                points.push_back(_3f(r2 * cos(a1) , 0, r2 * sin(a1)));
        
                points.push_back(_3f(r2 * cos(a1) , 0, r2 * sin(a1)));
                points.push_back(_3f(r1 * cos(a2) , 0, r1 * sin(a2)));
                points.push_back(_3f(r2 * cos(a2) , 0, r2 * sin(a2)));
        }
    }
    
    this->points.push_back(GSPoints(GL_TRIANGLES, points));
}

void Ring::Print(ostream &) const {
    cout << "Geometric Shape: Ring" << endl;
    cout << "Inner Radius:" << this->innerRadius << endl;
    cout << "Outer Radius:" << this->outerRadius << endl;
    cout << "Slices:" << this->slices << endl;
    cout << "Segments:" << this->segments << endl;
}
