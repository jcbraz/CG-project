//
// Created by user13 on 03-03-2023.
//

#include "geometricShapes.h"
#include "box.cpp"
#include "sphere.cpp"
#include "plane.cpp"   
#include "cone.cpp"
#include "ring.cpp"

#include <sstream>




// ILubyte * readImage(string fpath, int * width, int * height) {
//     ILuint t;

//     ilGenImages(1, &t);
//     ilBindImage(t);
//     ilLoadImage((ILstring) fpath.c_str());
//     ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);

//     ILenum error = ilGetError();
//     if (error != IL_NO_ERROR) {
//         cout << "Error loading image!" << ilGetString(error) << endl;
//     }

//     *width = ilGetInteger(IL_IMAGE_WIDTH);
//     *height = ilGetInteger(IL_IMAGE_HEIGHT);

//     //int size = *width * *height * ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
//     //ILubyte * imageData = new ILubyte[size];
//     //ILboolean result = ilCopyPixels(0, 0, 0, *width, *height, 1, IL_LUMINANCE, IL_UNSIGNED_BYTE, imageData);
//     ILubyte * imageData = ilGetData();
//     ILubyte * tmp = imageData;

//     if (!imageData)
//         cout << "error getting image data!" << endl;

//    // if (!result)
//      //   cout << "error getting data!" << endl << ilGetString(ilGetError()) << endl;

//     cout << "Loaded Image! W:" << *width << "H:" << *height << endl;
//     return imageData;
// }

// unsigned char * genRandomData(int h, int w) {
//     unsigned char * data = (unsigned char *) malloc(sizeof(unsigned char) * h*w);
//     for (int i = 0; i < h*w; i++) {
//         data[i] = (unsigned char) rand();
//     }
//     return data;
// }

// float height(int i, int j, ILubyte * imageData, int width, float multiplier) {
//     float h = imageData[i *  width + j];
//     return h / 255.0f * multiplier;
// }





/*
 *
 * END RING CLASS
 *
 */






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

void GeometricShape::drawObjectVBOMode(vector<VBOStruct> vbos, GLuint texture) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    for (auto vbo : vbos) {
        glBindBuffer(GL_ARRAY_BUFFER, vbo.points);
        glVertexPointer(3, GL_FLOAT, 0 ,0);

        if (vbo.normals != 0) {
            glBindBuffer(GL_ARRAY_BUFFER, vbo.normals);
            glNormalPointer(GL_FLOAT, 0, 0);
        }

        if (texture) {
            glBindBuffer(GL_ARRAY_BUFFER, texture);
            glTexCoordPointer(3, GL_FLOAT, 0, 0);
        }

        glDrawArrays(vbo.primitive, 0, vbo.size);
    }
}

void GeometricShape::writeTo3DFile(vector<GSPoints> gsps, string fName) {
    ofstream file(fName);
    cout << "Writing Points to:" << fName << endl;
    
    for (GSPoints gsp : gsps) {
        file << gsp.getPrimitive() << " " << gsp.getPoints().size() << endl;
        vector<_3f> points = gsp.getPoints();
        vector<_3f> normals = gsp.getNormals();
        for (int i = 0; i < points.size(); i++) {


            file << setprecision(FLOAT_PRECISION) << points[i].x << " " << points[i].y << " " << points[i].z;
            if (normals.size() > 0)
                    file << " " << normals[i].x << " " << normals[i].y << " " << normals[i].z;
            file << endl; 
        }

    }
    file.close();
    cout << "Done!" << endl;
}

#define SIZE_BUFFER 2048

vector<GSPoints> GeometricShape::readFromBezierPatchFile(string pathFName,  int tesselation) {
	vector<GSPoints> gspoints;
    vector <_3f> points;
    char line[SIZE_BUFFER];
	int j;
	int nPontos;
	int nPatches;
	FILE* f = fopen(pathFName.c_str(), "r");
	if (!f) {
		printf("Couldn't open file %s!\n", pathFName.c_str());
		return gspoints;
	}
	fscanf(f, "%d\n", &nPatches);

	int ** indexes = (int**)malloc(sizeof(int*) * nPatches);
	for (int i = 0; i < nPatches; i++) {
		indexes[i] = (int*)malloc(sizeof(int) * 16);
		memset(line, 0, SIZE_BUFFER);
		fgets(line, SIZE_BUFFER, f);
		char* token = NULL;
		for (j = 0, token = strtok(line, ", "); token && j < 16; token = strtok(NULL, ", "), j++) {
			indexes[i][j] = atoi(token);
		}
	}

	fscanf(f, "%d\n", &nPontos);
	float * XPoints = (float*)malloc(sizeof(float) * nPontos);
	float * YPoints = (float*)malloc(sizeof(float) * nPontos);
	float * ZPoints = (float*)malloc(sizeof(float) * nPontos);

	for (int k = 0; k < nPontos; k++) {
		memset(line, 0, SIZE_BUFFER);
		fgets(line, SIZE_BUFFER, f);
		XPoints[k] = atof(strtok(line, ", "));
		YPoints[k] = atof(strtok(NULL, ", "));
		ZPoints[k] = atof(strtok(NULL, ", "));
	}
	fclose(f);

	float arrX[16];
	float arrY[16];
	float arrZ[16];

	for (int i = 0; i <nPatches; i++) {
		for (int j = 0; j < 16; j++) {
			arrX[j] = XPoints[indexes[i][j]];
			arrY[j] = YPoints[indexes[i][j]];
			arrZ[j] = ZPoints[indexes[i][j]];
		}
		for (int u = 0; u < tesselation; u++) {
			float p0[3];
			float p1[3];
			float p2[3];
			float p3[3];
			for (int v = 0; v < tesselation; v++) {
				getBezierPoint(u / (float)tesselation, v / (float)tesselation, arrX, arrY, arrZ, p0);
				getBezierPoint((u + 1) / (float)tesselation, v / (float)tesselation, arrX, arrY, arrZ, p1);
				getBezierPoint(u / (float)tesselation, (v + 1) / (float)tesselation, arrX, arrY, arrZ, p2);
				getBezierPoint((u + 1) / (float)tesselation, (v + 1) / (float)tesselation, arrX, arrY, arrZ, p3);

                points.push_back(_3f(p0[0], p0[1], p0[2]));
                points.push_back(_3f(p3[0], p3[1], p3[2]));
                points.push_back(_3f(p2[0], p2[1], p2[2]));
                
                points.push_back(_3f(p1[0], p1[1], p1[2]));
                points.push_back(_3f(p3[0], p3[1], p3[2]));
                points.push_back(_3f(p0[0], p0[1], p0[2]));

		    }
        }
	}
    gspoints.push_back(GSPoints(GL_TRIANGLES, points));
	return gspoints;

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
    vector<GSPoints> gspoints;
    ifstream file(fName);

    if (!file) {
        cout << "File " << fName << " doesn't exist!" << endl;
        return gspoints;
    }

    cout << "Reading From:" << fName << endl;

    string line;
    bool readingPoints = false;
    int k;
    vector<_3f> pts; 
    vector<_3f> normals;
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
            if (nms.size() >  3) {
                normals.push_back(_3f(nms[3], nms[4], nms[5]));
            } 
            k--;
        
            if (k == 0) {
                gspoints.push_back(GSPoints(primitive, pts, normals));
                pts.clear();
                readingPoints = false;
            }
        }
    }
    file.close();
    cout << "Done!" << endl;
    return gspoints;
}

vector<VBOStruct> GeometricShape::convertToVBO(vector<GSPoints> gsps) {
    vector<VBOStruct> res;
    for (GSPoints gsp : gsps) {

        vector<float> points;
        vector<float> normals;
        for (_3f p : gsp.getPoints()) {
            points.push_back(p.x);
            points.push_back(p.y);
            points.push_back(p.z);
        }

        for (_3f n : gsp.getNormals()) {
            normals.push_back(n.x);
            normals.push_back(n.y);
            normals.push_back(n.z);
        }
        GLuint pointsVBO;
        glGenBuffers(1, &pointsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
        glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), points.data(), GL_STATIC_DRAW);

        GLuint normalsVBO = 0;
        if (gsp.getNormals().size() > 0) {
            glGenBuffers(1, &normalsVBO);
            glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
            glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), normals.data(), GL_STATIC_DRAW);
        }
        res.push_back(VBOStruct(pointsVBO, normalsVBO, gsp.getPrimitive(), gsp.getPoints().size()));
    }

    return res;

}

vector<VBOStruct> GeometricShape::readFrom3DFileVBOMode(string fName) {
    vector<VBOStruct> res;
    vector<GSPoints> gsps = GeometricShape::readFrom3DFile(fName);

    res = GeometricShape::convertToVBO(gsps);

    return res;
}

GLuint GeometricShape::loadTextureImageVBO(string pathFile) {
    GLuint texture;
    unsigned int t, tw, th;
    unsigned char *texData;
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring)pathFile.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texture);
    
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}