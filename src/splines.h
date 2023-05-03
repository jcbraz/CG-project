#ifndef __SPLINES_H__
#define __SPLINES_H__

#include <vector>
#include <math.h>
#include <iostream>
#include "geometricShapes.h"

// Catmull-Rom splines
void getGlobalCatmullRomPoint(float gt, _3f * pos, _3f * deriv, vector<_3f> catmrPts);

// Bezier splines
void getBezierPoint(float u, float v, float* px, float* py, float* pz, float* normalV);

void buildRotMatrix(_3f x, _3f y, _3f z, float * rotMatrix);

#endif