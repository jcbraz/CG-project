//
// Created by user13 on 03-03-2023.
//

#include "geometricShapes.h"

#include <sstream>




ILubyte * readImage(string fpath, int * width, int * height) {
    ILuint t;

    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring) fpath.c_str());
    ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);

    ILenum error = ilGetError();
    if (error != IL_NO_ERROR) {
        cout << "Error loading image!" << ilGetString(error) << endl;
    }

    *width = ilGetInteger(IL_IMAGE_WIDTH);
    *height = ilGetInteger(IL_IMAGE_HEIGHT);

    //int size = *width * *height * ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
    //ILubyte * imageData = new ILubyte[size];
    //ILboolean result = ilCopyPixels(0, 0, 0, *width, *height, 1, IL_LUMINANCE, IL_UNSIGNED_BYTE, imageData);
    ILubyte * imageData = ilGetData();
    ILubyte * tmp = imageData;

    if (!imageData)
        cout << "error getting image data!" << endl;

   // if (!result)
     //   cout << "error getting data!" << endl << ilGetString(ilGetError()) << endl;

    cout << "Loaded Image! W:" << *width << "H:" << *height << endl;
    return imageData;
}

unsigned char * genRandomData(int h, int w) {
    unsigned char * data = (unsigned char *) malloc(sizeof(unsigned char) * h*w);
    for (int i = 0; i < h*w; i++) {
        data[i] = (unsigned char) rand();
    }
    return data;
}

float height(int i, int j, ILubyte * imageData, int width, float multiplier) {
    float h = imageData[i *  width + j];
    return h / 255.0f * multiplier;
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

Sphere::Sphere(float radius, int slices, int stacks, float multiplier, string fileName) : radius(radius), slices(slices), stacks(stacks) {
    this->fileName = fileName;
    float _alpha = 2 * M_PI / slices;
    float _beta = M_PI / stacks;
    unsigned char * imageData = genRandomData(this->slices, this->stacks);
    for (int i = 0; i < slices-1; i++) {
        vector<_3f> strip;
        float av1 = i * _alpha;
        float av2 = av1 + _alpha;

        for (int j = 0; j <= stacks; j++) {
            float bv1 = -M_PI/2 + j * _beta;
            

            float hr1 = this->radius - height(i, j, imageData, this->slices, multiplier);
            float hr2 = this->radius - height(i+1, j, imageData, this->slices, multiplier);
            strip.push_back(
                _3f(
                    hr1 * cos(bv1) * sin(av1),
                    hr1 * sin(bv1),
                    hr1 * cos(bv1) * cos(av1)
                )
            );

            strip.push_back(
                _3f(
                    hr2 * cos(bv1) * sin(av2),
                    hr2 * sin(bv1),
                    hr2 * cos(bv1) * cos(av2)
                )
            );


        }
        this->points.push_back(GSPoints(GL_TRIANGLE_STRIP, strip));        
    }  

    vector<_3f> strip;
    float av1 = (this->slices-1) * _alpha;
    float av2 = 0;

    for (int j = 0; j <= stacks; j++) {
        float bv1 = -M_PI/2 + j * _beta;
        

        float hr1 = this->radius - height(this->slices-1, j, imageData, this->slices, multiplier);
        float hr2 = this->radius - height(0, j, imageData, this->slices, multiplier);
        strip.push_back(
            _3f(
                hr1 * cos(bv1) * sin(av1),
                hr1 * sin(bv1),
                hr1 * cos(bv1) * cos(av1)
            )
        );

        strip.push_back(
            _3f(
                hr2 * cos(bv1) * sin(av2),
                hr2 * sin(bv1),
                hr2 * cos(bv1) * cos(av2)
            )
        );


    }
    this->points.push_back(GSPoints(GL_TRIANGLE_STRIP, strip));        
}

Sphere::Sphere(string specularMap, string fileName, float radius, float multiplier) : radius(radius) {
    this->fileName = fileName;
    ILubyte * imageData = readImage(specularMap, &this->slices, &this->stacks);
    float _alpha = 2 * M_PI / slices;
    float _beta = M_PI / stacks;
    for (int i = 0; i < slices-1; i++) {
        vector<_3f> strip;
        float av1 = i * _alpha;
        float av2 = av1 + _alpha;

        for (int j = 0; j <= stacks; j++) {
            float bv1 = -M_PI/2 + j * _beta;
            

            float hr1 = this->radius - height(i, j, imageData, this->slices, multiplier);
            float hr2 = this->radius - height(i+1, j, imageData, this->slices, multiplier);
            strip.push_back(
                _3f(
                    hr1 * cos(bv1) * sin(av1),
                    hr1 * sin(bv1),
                    hr1 * cos(bv1) * cos(av1)
                )
            );

            strip.push_back(
                _3f(
                    hr2 * cos(bv1) * sin(av2),
                    hr2 * sin(bv1),
                    hr2 * cos(bv1) * cos(av2)
                )
            );


        }
        this->points.push_back(GSPoints(GL_TRIANGLE_STRIP, strip));        
    }  

    vector<_3f> strip;
    float av1 = (this->slices-1) * _alpha;
    float av2 = 0;

    for (int j = 0; j <= stacks; j++) {
        float bv1 = -M_PI/2 + j * _beta;
        

        float hr1 = this->radius - height(this->slices-1, j, imageData, this->slices, multiplier);
        float hr2 = this->radius - height(0, j, imageData, this->slices, multiplier);
        strip.push_back(
            _3f(
                hr1 * cos(bv1) * sin(av1),
                hr1 * sin(bv1),
                hr1 * cos(bv1) * cos(av1)
            )
        );

        strip.push_back(
            _3f(
                hr2 * cos(bv1) * sin(av2),
                hr2 * sin(bv1),
                hr2 * cos(bv1) * cos(av2)
            )
        );


    }
    this->points.push_back(GSPoints(GL_TRIANGLE_STRIP, strip));        
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
		printf("Couldn't open file %s!\n", pathFName);
		return gspoints;
	}
	fscanf(f, "%d\n", &nPatches);	//printf("%d\n", patches);

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

vector<std::tuple<GLuint, int, int>> GeometricShape::convertToVBO(vector<GSPoints> gsps) {
    vector<std::tuple<GLuint, int, int>> res;
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

vector<std::tuple<GLuint, int, int>> GeometricShape::readFrom3DFileVBOMode(string fName) {
    vector<std::tuple<GLuint, int, int>> res;
    vector<GSPoints> gsps = GeometricShape::readFrom3DFile(fName);

    res = GeometricShape::convertToVBO(gsps);

    return res;
}
