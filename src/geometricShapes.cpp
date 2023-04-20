//
// Created by user13 on 03-03-2023.
//

#include "geometricShapes.h"

#include <sstream>

/*
 *
 * POINT STRUCT
 *
 */

_3f::_3f(float x, float y, float z) {
    _3f::x = x;
    _3f::y = y;
    _3f::z = z;
}

_3f::_3f() {
    _3f::x = 0;
    _3f::y = 0;
    _3f::z = 0;
}

void _3f::normalize() {
    float max = abs(x);
    if (abs(y) > max) max = abs(y);
    if (abs(z) > max) max = abs(z);

    x = x / max;
    y = y / max;
    z = z / max;
}  

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
    float n_d = (float) length / (float) divisions;
    float h_l = (float) length / 2;
    for (int i = 0; i < divisions; i++) {
        for (int j = 0; j < divisions; j++) {
            //primeiro triangulo
            points.push_back(_3f(-h_l + n_d * j, 0, -h_l+ n_d * i));
            points.push_back(_3f(-h_l + n_d * j, 0, -h_l + n_d * (i+1)));
            points.push_back(_3f(-h_l + n_d * (j+1), 0, -h_l + n_d * i));
            //segundo triangulo
            points.push_back(_3f(-h_l + n_d * j, 0, -h_l + n_d * (i+1)));
            points.push_back(_3f(-h_l + n_d * (j+1), 0, -h_l + n_d * (i+1)));
            points.push_back(_3f(-h_l + n_d * (j+1), 0, -h_l + n_d * i));
        }
    }

    this->points.push_back(GSPoints(GL_TRIANGLES, points));
}

void Plane::Print(ostream &) const {
    cout << "Geometric Shape:Plane" << endl;
    cout << "Length:" << Plane::length << endl;
    cout << "Divisions:" << Plane::divisions << endl;
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
    this->length = length;
    this->divisions = divisions;
    this->fileName = std::move(pathFile);

    vector<_3f> points;
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

            points.push_back(_3f(x+division_size, y, -measure));
            points.push_back(_3f(x, y+division_size, -measure));
            points.push_back(_3f(x+division_size, y+division_size, -measure));


            points.push_back(_3f(x, y, measure));
            points.push_back(_3f(x+division_size, y, measure));
            points.push_back(_3f(x, y+division_size, measure));

            points.push_back(_3f(x+division_size, y, measure));
            points.push_back(_3f(x+division_size, y+division_size, measure));
            points.push_back(_3f(x, y+division_size, measure));

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


            points.push_back(_3f(x+division_size, measure, z));
            points.push_back(_3f(x, measure, z+division_size));
            points.push_back(_3f(x+division_size, measure, z+division_size));

            // Bottom
            points.push_back(_3f(x, -measure, z));
            points.push_back(_3f(x+division_size, -measure, z));
            points.push_back(_3f(x, -measure, z+division_size));


            points.push_back(_3f(x+division_size, -measure, z));
            points.push_back(_3f(x+division_size, -measure, z+division_size));
            points.push_back(_3f(x, -measure, z+division_size));

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


            points.push_back(_3f(-measure, y+division_size, z));
            points.push_back(_3f(-measure, y, z+division_size));
            points.push_back(_3f(-measure, y+division_size, z+division_size));


            points.push_back(_3f(measure, y, z));
            points.push_back(_3f(measure, y+division_size, z));
            points.push_back(_3f(measure, y, z+division_size));


            points.push_back(_3f(measure, y+division_size, z));
            points.push_back(_3f(measure, y+division_size, z+division_size));
            points.push_back(_3f(measure, y, z+division_size));

        }
    }


    this->points.push_back(GSPoints(GL_TRIANGLES, points));
}


void Box::Print(ostream &) const {
    cout << "Geometric Shape: Box" << endl;
    cout << "Length:" << Box::length << endl;
    cout << "Divisions:" << Box::divisions << endl;
}

/*
 *
 * END BOX CLASS
 *
 */


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

/*
 *
 * END RING CLASS
 *
 */

/*
 *
 * SPHERE CLASS
 *
 */

Sphere::Sphere() {
    radius = 1;
    slices = 10;
    stacks = 3;
    fileName = "sphere.3d";
}

Sphere::Sphere(float radius, int slices, int stacks) {
    Sphere::radius = radius;
    Sphere::slices = slices;
    Sphere::stacks = stacks;
    fileName = "sphere.3d";
}

Sphere::Sphere(string specularMap, string fileName) {
    /*
    ILuint t;
    ilInit();
    ilGenImages(1, &t);
    ilBindImage(t);

    ilLoadImage((ILstring) specularMap.c_str());
    ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);

    this->slices = ilGetInteger(IL_IMAGE_WIDTH);
    this->stacks = ilGetInteger(IL_IMAGE_HEIGHT);
    
    ILubyte * imageData;
    imageData = ilGetData();

    */
}

Sphere::Sphere(float radius, int slices, int stacks, string fileName) {
    this->radius = radius;
    this->slices = slices;
    this->stacks = stacks;
    this->fileName = std::move(fileName);

    vector<_3f> points;

    float _alpha = 2 * M_PI / slices;
    float _beta = M_PI / stacks;
    float r = radius;
    for (int j = 0; j < stacks; j++) {
        float bv = -M_PI/2 + j * _beta;
        float bhv = bv + _beta;

        for (int i = 0; i < slices; i++) {
            float av = i * _alpha;
            float ahv = av + _alpha;
            points.push_back(_3f(r * cos(bv) * sin(av), r * sin(bv) ,r * cos(bv) * cos(av)));
            points.push_back(_3f(r * cos(bv) * sin(ahv), r * sin(bv) ,r * cos(bv) * cos(ahv)));
            points.push_back(_3f(r * cos(bhv) * sin(ahv), r * sin(bhv) ,r * cos(bhv) * cos(ahv)));

            points.push_back(_3f(r * cos(bv) * sin(av), r * sin(bv) ,r * cos(bv) * cos(av)));
            points.push_back(_3f(r * cos(bhv) * sin(ahv), r * sin(bhv) ,r * cos(bhv) * cos(ahv)));
            points.push_back(_3f(r * cos(bhv) * sin(av), r * sin(bhv) ,r * cos(bhv) * cos(av)));
        }
    }

    this->points.push_back(GSPoints(GL_TRIANGLES, points));
}

void Sphere::Print(ostream &) const {
    cout << "Geometric Shape: Sphere" << endl;
    cout << "Radius:" << Sphere::radius << endl;
    cout << "Slices:" << Sphere::slices << endl;
    cout << "Stacks:" << Sphere::stacks << endl;
}
/*
 *
 * END SPHERE CLASS
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


/*
 *
 * END CONE CLASS
 *
 */

/*
 *
 * END POINT STRUCT
 *
 */
void GeometricShape::drawObject(vector<GSPoints> points) {
    for (GSPoints gsp : points) {
        glBegin(gsp.getPrimitive());
            vector<_3f> pts = gsp.getPoints();
            for (auto p : pts)
                glVertex3f(p.x, p.y, p.z);
        glEnd();
    }
}

void GeometricShape::drawObjectVBOMode(vector<std::tuple<GLuint, int, int>> v) {
    for (auto t : v) {
        glBindBuffer(GL_ARRAY_BUFFER, std::get<0>(t));
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0 ,0);
        glDrawArrays(std::get<1>(t), 0, std::get<2>(t));
    }
}

void GeometricShape::writeTo3DFile(vector<GSPoints> points, string fName) {
    ofstream file(fName);
    cout << "Writing Points to:" << fName << endl;
    for (GSPoints gsp : points) {
        vector<_3f> ps = gsp.getPoints();
        file << gsp.getPrimitive() << " " << ps.size() << endl;
        for (_3f p : ps) {
            file << setprecision(FLOAT_PRECISION) << p.x << " " << p.y << " " << p.z << endl;
        }
    }
    file.close();
    cout << "Done!" << endl;
}

vector<int> _readInts(string line) {
    vector<int> nms;
    std::istringstream ss(line);
    int num;
    while (ss >> num) {
        nms.push_back(num);
    }
    return nms;
}

vector<float> _readFloats(string line) {
    vector<float> nms;
    std::istringstream ss(line);
    float num;
    while (ss >> num) {
        nms.push_back(num);
    }
    return nms;
}

vector<GSPoints> GeometricShape::readFrom3DFile(string fName) {
    vector<GSPoints> points;
    ifstream file(fName);

    if (!file) {
        cout << "File " << fName << " doesn't exist!" << endl;
        return points;
    }

    cout << "Reading From:" << fName << endl;

    string line;
    bool readingPoints = false;
    int k;
    vector<_3f> pts; 
    int primitive;
    while (getline(file, line)) {

        if (!readingPoints) {
            vector<int> prim_size = _readInts(line);
            for (auto p : prim_size)
                cout << "v:" << p << endl;
            readingPoints = true;
            primitive = prim_size[0];
            k = prim_size[1];
        } 
        else {
            vector<float> nms = _readFloats(line);
            pts.push_back(_3f(nms[0], nms[1], nms[2]));
            k--;
        
            if (k == 0) {
                points.push_back(GSPoints(primitive, pts));
                pts.clear();
                readingPoints = false;
            }
        }
    }
    file.close();
    cout << "Done!" << endl;
    return points;
}

vector<std::tuple<GLuint, int, int>> GeometricShape::readFrom3DFileVBOMode(string fName) {
    vector<std::tuple<GLuint, int, int>> res;
    vector<GSPoints> gsps = GeometricShape::readFrom3DFile(fName);

    for (GSPoints gsp : gsps) {
        
        vector<float> f_pts;
        for (_3f p : gsp.getPoints()) {
            f_pts.push_back(p.x);
            f_pts.push_back(p.y);
            f_pts.push_back(p.z);
        }

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, f_pts.size() * sizeof(float), f_pts.data(), GL_STATIC_DRAW);

        res.push_back(make_tuple(vbo, gsp.getPrimitive(), f_pts.size()));
    }

    return res;
}
