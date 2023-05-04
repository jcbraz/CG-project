#ifndef __SPLINES_H__
#define __SPLINES_H__

#include <vector>
#include <math.h>

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

void getGlobalCatmullRomPoint(float gt, _3f * pos, _3f * deriv, vector<_3f> catmrPts);

void getBezierPoint(float u, float v, float* px, float* py, float* pz, float* normalV);

void buildRotMatrix(_3f x, _3f y, _3f z, float * rotMatrix);

#endif