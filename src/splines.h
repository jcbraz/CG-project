#ifndef __SPLINES_H__
#define __SPLINES_H__

#include "geometricShapes.h"

void getGlobalCatmullRomPoint(float gt, _3f * pos, _3f * deriv, vector<_3f> catmrPts);

void buildRotMatrix(_3f x, _3f y, _3f z, float * rotMatrix);

#endif