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


// Sphere::Sphere(float radius, int slices, int stacks, float multiplier, string fileName) : radius(radius), slices(slices), stacks(stacks) {
//     this->fileName = fileName;
//     float _alpha = 2 * M_PI / slices;
//     float _beta = M_PI / stacks;
//     unsigned char * imageData = genRandomData(this->slices, this->stacks);
//     for (int i = 0; i < slices-1; i++) {
//         vector<_3f> strip;
//         float av1 = i * _alpha;
//         float av2 = av1 + _alpha;

//         for (int j = 0; j <= stacks; j++) {
//             float bv1 = -M_PI/2 + j * _beta;
            

//             float hr1 = this->radius - height(i, j, imageData, this->slices, multiplier);
//             float hr2 = this->radius - height(i+1, j, imageData, this->slices, multiplier);
//             strip.push_back(
//                 _3f(
//                     hr1 * cos(bv1) * sin(av1),
//                     hr1 * sin(bv1),
//                     hr1 * cos(bv1) * cos(av1)
//                 )
//             );

//             strip.push_back(
//                 _3f(
//                     hr2 * cos(bv1) * sin(av2),
//                     hr2 * sin(bv1),
//                     hr2 * cos(bv1) * cos(av2)
//                 )
//             );


//         }
//         this->points.push_back(GSPoints(GL_TRIANGLE_STRIP, strip));        
//     }  

//     vector<_3f> strip;
//     float av1 = (this->slices-1) * _alpha;
//     float av2 = 0;

//     for (int j = 0; j <= stacks; j++) {
//         float bv1 = -M_PI/2 + j * _beta;
        

//         float hr1 = this->radius - height(this->slices-1, j, imageData, this->slices, multiplier);
//         float hr2 = this->radius - height(0, j, imageData, this->slices, multiplier);
//         strip.push_back(
//             _3f(
//                 hr1 * cos(bv1) * sin(av1),
//                 hr1 * sin(bv1),
//                 hr1 * cos(bv1) * cos(av1)
//             )
//         );

//         strip.push_back(
//             _3f(
//                 hr2 * cos(bv1) * sin(av2),
//                 hr2 * sin(bv1),
//                 hr2 * cos(bv1) * cos(av2)
//             )
//         );


//     }
//     this->points.push_back(GSPoints(GL_TRIANGLE_STRIP, strip));        
// }

// Sphere::Sphere(string specularMap, string fileName, float radius, float multiplier) : radius(radius) {
//     this->fileName = fileName;
//     ILubyte * imageData = readImage(specularMap, &this->slices, &this->stacks);
//     float _alpha = 2 * M_PI / slices;
//     float _beta = M_PI / stacks;
    
//     for (int i = 0; i < slices-1; i++) {
//         vector<_3f> strip;

//         float av1 = i * _alpha;
//         float av2 = av1 + _alpha;

//         for (int j = 0; j <= stacks; j++) {

//             float bv1 = -M_PI/2 + j * _beta;
            

//             float hr1 = this->radius - height(j, i, imageData, this->slices, multiplier);
//             float hr2 = this->radius - height(j, i+1, imageData, this->slices, multiplier);
            
//             strip.push_back(
//                 _3f(
//                     hr1 * cos(bv1) * sin(av1),
//                     hr1 * sin(bv1),
//                     hr1 * cos(bv1) * cos(av1)
//                 )
//             );

//             strip.push_back(
//                 _3f(
//                     hr2 * cos(bv1) * sin(av2),
//                     hr2 * sin(bv1),
//                     hr2 * cos(bv1) * cos(av2)
//                 )
//             );

//         }
//         this->points.push_back(GSPoints(GL_TRIANGLE_STRIP, strip));    

//     }

//     vector<_3f> strip;
//     vector<_3f> normals;
//     float av1 = (this->slices-1) * _alpha;
//     float av2 = 0;

//     for (int j = 0; j <= stacks; j++) {
//         float bv1 = -M_PI/2 + j * _beta;
        

//         float hr1 = this->radius - height(this->slices-1, j, imageData, this->slices, multiplier);
//         float hr2 = this->radius - height(0, j, imageData, this->slices, multiplier);
//         strip.push_back(
//             _3f(
//                 hr1 * cos(bv1) * sin(av1),
//                 hr1 * sin(bv1),
//                 hr1 * cos(bv1) * cos(av1)
//             )
//         );

//         strip.push_back(
//             _3f(
//                 hr2 * cos(bv1) * sin(av2),
//                 hr2 * sin(bv1),
//                 hr2 * cos(bv1) * cos(av2)
//             )
//         );


//     }
//     this->points.push_back(GSPoints(GL_TRIANGLE_STRIP, strip));   
     
//     for (int i = 0; i < this->points.size()-1; i++) {

//         vector<_3f> strip = this->points[i].getPoints();

//         for (int k = 0; k < strip.size()-2; k++) {
//             _3f normal = _3f::cross(strip[k+1] - strip[k], strip[k+2] - strip[k]);
//             normal.normalize();
//             normals.push_back(normal);
//             normal = _3f::cross(strip[k+2] - strip[k+1], strip[k+3] - strip[k+1]); 
//             normal.normalize();
//             normals.push_back(normal);
//         }


//     for (int k = 0; k < strip.size(); k++) {
//             _3f normal = normals[k] + normals[k+1];
//             normal.normalize();
//             normals[k] = normal;
//         }

//         this->points[i].setNormals(normals);
//     }

    // for (int i = 0; i < this->points.size(); i++) {  
    //     for (int k = 0; k < strip.size(); k++) {
    //         _3f normal = _3f::cross(strip[k+1] - strip[k], strip[k+2] - strip[k]);
    //         normals.push_back(normal);
    //         normal = _3f::cross(strip[k+1] - strip[k], strip[k+4] - strip[k+1]); 
    //         normals.push_back(normal);
    //     }

    //     normals.insert(normals.begin(), normals[0]);
    //     normals.push_back(normals.back());

    //     for (int k = 0; k < strip.size(); k++) {
    //         _3f normal = normals[k] + normals[k+1];
    //         normal.normalize();
    //         normals[k] = normal;
    //     }

    //     this->points[i].setNormals(normals);
    // }
// }

