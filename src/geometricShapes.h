//
// Created by user13 on 03-03-2023.
//

#ifndef __GEOMETRICSHAPES_H__
#define __GEOMETRICSHAPES_H__


#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <tuple>

#include <IL/il.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else

#include <GL/glew.h>
#include <GL/glut.h>

#endif
#define GLUT_

#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include <cstring>
#include <iomanip>

#include "splines.h"

#define FLOAT_PRECISION 5

using namespace std;

/*
 *
 * POINT STRUCT
 *
 */

struct _3f {
    float x;
    float y;
    float z;

    public:
        _3f();
        _3f(float x, float y, float z);
        static _3f cross(_3f a, _3f b);//cross product
        void normalize();
        _3f operator+(const _3f& other) const { return _3f(x + other.x, y + other.y, z + other.z); }
        _3f operator+(const float& other) const { 
            cout << x << " " << y << " " << z << endl;
            return _3f(x + other, y + other, z + other); 
        }
        _3f operator-(const _3f& other) const { return _3f(x - other.x, y - other.y, z - other.z); }
        _3f operator*(const _3f& other) const { return _3f(x * other.x, y * other.y, z * other.z); }
        _3f operator*(const float& other) const { return _3f(x * other, y * other, z * other); }

};

/*
 *
 * END POINT STRUCT
 *
 */

/*
 *
 * GEOMETRIC OBJECT ABSTRACT CLASS
 *
 */

class GSPoints {
    private:
        int primitive;
        vector<_3f> points;
    public:
        GSPoints(int primitive, vector<_3f> points) : primitive(primitive), points(points) {};
        int getPrimitive() {return this->primitive;};
        vector<_3f> getPoints() {return this->points;};
};

class GeometricShape {
protected:
    vector<GSPoints> points;
    string fileName;

public:
    virtual vector<GSPoints> getPoints() {return points;};

    static void drawObject(vector<GSPoints> points);
    static void drawObjectVBOMode(vector<std::tuple<GLuint, int, int>>);

    static void writeTo3DFile(vector<GSPoints> points, string fName);
    static vector<std::tuple<GLuint, int, int>>convertToVBO(vector<GSPoints> gsps);
    static vector<GSPoints> readFrom3DFile(string fName);
    static vector<std::tuple<GLuint, int, int>> readFrom3DFileVBOMode(string fName);
    static vector<GSPoints> readFromBezierPatchFile(string pathFName,  int tesselation);

    string getFileName() { return fileName; }


    friend ostream &operator<<(ostream &out, const GeometricShape &go) {
        go.Print(out);
        return out;
    }

private:
    virtual void Print(ostream &) const = 0;
};

/*
 *
 * END GEOMETRIC OBJECT ABSTRACT CLASS
 *
 */

class Circumference : public GeometricShape {
    private:
        float radius;
        int slices;

    public:
        Circumference(float radius, int slices) : radius(radius), slices(slices) {};

    protected:
        void Print(ostream &) const override;
    
};

class Ring : public GeometricShape {
    private:
        float innerRadius;
        float outerRadius;
        int slices;
        int segments;
    public:
        Ring(float innerRadius, float outerRadius, int slices, int segments, string fName);
        
    protected:
        void Print(ostream &) const override;
};

class Torus : public GeometricShape {
    private:
        float innerRadius;
        float outerRadius;
        int slices;
        int loops;

    public:    
        /*
            POR IMPLEMENTAR
        */
        Torus();
        Torus(float innerRadius, float outerRadius, int slices, int loops);
        Torus(float innerRadius, float outerRadius, int slices, int loops, string pathFile);

    protected:
        void Print(ostream &) const override;
};

/*
 *
 * CONE CLASS
 *
 */

class Cone : public GeometricShape {
    private:
        float radius;
        float height;
        int slices;
        int stacks;

    public:
        Cone();
        Cone(float radius, float height, int slices, int stacks);
        Cone(float radius, float height, int slices, int stacks, string pathFile);

    protected:
        void Print(ostream &) const override;
};

/*
 *
 * END CONE CLASS
 *
 */


/*
 *
 * PLANE CLASS
 *
 */
class Plane : public GeometricShape {
    private:
        float length;
        int divisions;

    public:
        Plane();
        Plane(float length, int divisions);
        Plane(float length, int divisions, string fileName);

    protected:
        void Print(ostream &) const override;
};

/*
 *
 * END PLANE CLASS
 *
 */

/*
 *
 * BOX CLASS
 *
 */
class Box : public GeometricShape {
private:
    float length;
    int divisions;

public:
    Box();
    Box(float length, int divisions);
    Box(float length, int divisions, string pathFile);

protected:
    void Print(ostream &) const override;
};

/*
 *
 * END BOX CLASS
 *
 */

/*
 *
 * SPHERE CLASS
 *
 */
class Sphere : public GeometricShape {
    private:
        float radius;
        int slices;
        int stacks;

    public:
        Sphere(float radius, int slices, int stacks);
        Sphere(float radius, int slices, int stacks, string pathFile);
        Sphere(string specularMap, string fileName, float radius, float multiplier);
        Sphere(float radius, int slices, int stacks, float multiplier, string fileName);

    protected:
        void Print(ostream &) const override;
};

/*
 *
 * END SPHERE CLASS
 *
 */

#endif //__GEOMETRICSHAPES_H__
