#include "splines.h"

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

_3f _3f::cross(_3f a, _3f b) {
    return _3f(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

void _3f::normalize() {
    float l = sqrt(x*x + y*y + z*z);
    x /= l;
    y /= l;
    z /= l;
}  

void multMatrixVector(float m[4][4], float * v, float * res) {
    for (int j = 0; j < 4; ++j) {
		res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j][k];
        }
	}
}

void mult1dMatrixVector(float* m, float* v, float* res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}

}

void mult1dVectorMatrix(float* v, float* m, float* res) {

	for (int j = 0; j < 4; ++j) {
		res[j] = 0;
		for (int k = 0; k < 4; ++k) {
			res[j] += v[k] * m[j * 4 + k];
		}
	}
}

void normalize(float* a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}

void getCatmullRomPoint(float t, _3f p0, _3f p1, _3f p2, _3f p3, _3f * pos, _3f * deriv) {
    // catmull-rom matrix
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
						{ 1.0f, -2.5f,  2.0f, -0.5f},
						{-0.5f,  0.0f,  0.5f,  0.0f},
						{ 0.0f,  1.0f,  0.0f,  0.0f}};

    float px[4] = {p0.x, p1.x, p2.x, p3.x};
    float ax[4];
    multMatrixVector(m, px, ax);
    pos->x = powf(t,3.0) * ax[0] + powf(t,2.0) * ax[1] + t * ax[2] + ax[3];
    deriv->x = 3*powf(t,2.0) * ax[0] + 2 * t * ax[1] + ax[2];

    float py[4] = {p0.y, p1.y, p2.y, p3.y};
    float ay[4];
    multMatrixVector(m, py, ay);
    pos->y = powf(t,3.0) * ay[0] + powf(t,2.0) * ay[1] + t * ay[2] + ay[3];
    deriv->y = 3*powf(t,2.0) * ay[0] + 2 * t * ay[1] + ay[2];

    float pz[4] = {p0.z, p1.z, p2.z, p3.z};
    float az[4];
    multMatrixVector(m, pz, az);
    pos->z = powf(t,3.0) * az[0] + powf(t,2.0) * az[1] + t * az[2] + az[3];
    deriv->z = 3*powf(t,2.0) * az[0] + 2 * t * az[1] + az[2];
}





void getGlobalCatmullRomPoint(float gt, _3f * pos, _3f * deriv, vector<_3f> catmrPts) {
    float t = gt * catmrPts.size();
    int index = floor(t);
    t = t - index;

    int indexes[4];
    indexes[0] = (index + catmrPts.size()-1) % catmrPts.size();
    indexes[1] = (indexes[0] + 1) % catmrPts.size();
    indexes[2] = (indexes[1] + 1) % catmrPts.size();
    indexes[3] = (indexes[2] + 1) % catmrPts.size();

    getCatmullRomPoint(t, catmrPts[indexes[0]], catmrPts[indexes[1]], catmrPts[indexes[2]], catmrPts[indexes[3]], pos, deriv);
}

void buildRotMatrix(_3f x, _3f y, _3f z,  float * m) {

    m[0] = x.x; m[1] = x.y; m[2] = x.z; m[3] = 0;
    m[4] = y.x; m[5] = y.y; m[6] = y.z; m[7] = 0;
    m[8] = z.x; m[9] = z.y; m[10] = z.z; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}

void getBezierPoint(float u, float v, float* px, float* py, float* pz, float* normalV) {

	float m[4][4] = { {-1.0f,  3.0f, -3.0f,  1.0f},
					  { 3.0f, -6.0f,  3.0f,  0.0f},
					  {-3.0f,  3.0f,  0.0f,  0.0f},
					  { 1.0f,  0.0f,  0.0f,  0.0f}
	};

	float Px[4][4] = { {px[0],  px[1],  px[2],  px[3] },
					   {px[4],  px[5],  px[6],  px[7] },
					   {px[8],  px[9],  px[10], px[11]},
					   {px[12], px[13], px[14], px[15]}
	};

	float Py[4][4] = { {py[0],  py[1],  py[2],  py[3] },
					   {py[4],  py[5],  py[6],  py[7] },
					   {py[8],  py[9],  py[10], py[11]},
					   {py[12], py[13], py[14], py[15]}
	};

	float Pz[4][4] = { {pz[0],  pz[1],  pz[2],  pz[3] },
					   {pz[4],  pz[5],  pz[6],  pz[7] },
					   {pz[8],  pz[9],  pz[10], pz[11]},
					   {pz[12], pz[13], pz[14], pz[15]}
	};

	float U[4] = { u * u * u , u * u , u, 1 };
	float Ud[4] = { 3 * u * u , 2 * u, 1, 0 };

	float V[4] = { v * v * v , v * v , v, 1 };
	float Vd[4] = { 3 * v * v , 2 * v, 1, 0 };

	float UM[4];
	mult1dVectorMatrix(U, (float*)m, UM);
	float UMd[4];
	mult1dVectorMatrix(Ud, (float*)m, UMd);

	float MV[4];
	mult1dMatrixVector((float*)m, V, MV);
	float MVd[4];
	mult1dMatrixVector((float*)m, Vd, MVd);

	float UMP[3][4];
	mult1dVectorMatrix(UM, (float*)Px, UMP[0]);
	mult1dVectorMatrix(UM, (float*)Py, UMP[1]);
	mult1dVectorMatrix(UM, (float*)Pz, UMP[2]);

	float UMPd[3][4];
	mult1dVectorMatrix(UMd, (float*)Px, UMPd[0]);
	mult1dVectorMatrix(UMd, (float*)Py, UMPd[1]);
	mult1dVectorMatrix(UMd, (float*)Pz, UMPd[2]);

	float derivU[3];
	float derivV[3];

	for (int i = 0; i < 3; i++) {
		normalV[i] = 0.0f;
		derivU[i] = 0.0f;
		derivV[i] = 0.0f;

		for (int j = 0; j < 4; j++) {
			normalV[i] += MV[j] * UMP[i][j];
			derivU[i] += UMPd[i][j] * MV[j];
			derivV[i] += UMP[i][j] * MVd[j];
		}
	}

	normalize(derivU);
	normalize(derivV);
	//cross(derivU, derivV,normalV);
	//normalize(normalV);
}