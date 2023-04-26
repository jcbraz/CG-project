#include "splines.h"

void multMatrixVector(float m[4][4], float * v, float * res) {
    for (int j = 0; j < 4; ++j) {
		res[j] = 0;
        for (int k = 0; k < 4; ++k) {
            res[j] += v[k] * m[j][k];
        }
	}
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

    int indexes[4];
    indexes[0] = (index + catmrPts.size()-1) % catmrPts.size();
    indexes[1] = (indexes[0] + 1) % catmrPts.size();
    indexes[2] = (indexes[1] + 1) % catmrPts.size();
    indexes[3] = (indexes[2] + 1) % catmrPts.size();

    getCatmullRomPoint(t, catmrPts[indexes[0]], catmrPts[indexes[1]], catmrPts[indexes[2]], catmrPts[indexes[3]], pos, deriv);
}

