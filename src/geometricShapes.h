//
// Created by user13 on 03-03-2023.
//

#ifndef GROUP_PROJECT_GEOMETRICSHAPES_H
#define GROUP_PROJECT_GEOMETRICSHAPES_H

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

class GeometricShape {
protected:
    int vertices;
    string fileName;

public:
    virtual vector<_3f> getPoints() = 0;

    static void drawObject(vector<_3f> points);

    static void writeTo3DFile(vector<_3f> points, string fName);

    static vector<_3f> readFrom3DFile(string fName);

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

        vector<_3f> getPoints() override;

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
        
        vector<_3f> getPoints() override;

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
        vector<_3f> getPoints() override;

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
        vector<_3f> getPoints() override;

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
        vector<_3f> getPoints() override;

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
    vector<_3f> getPoints() override;

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
        Sphere();
        Sphere(float radius, int slices, int stacks);
        Sphere(float radius, int slices, int stacks, string pathFile);
        vector<_3f> getPoints() override;

    protected:
        void Print(ostream &) const override;
};

/*
 *
 * END SPHERE CLASS
 *
 */

#endif //GROUP_PROJECT_GEOMETRICSHAPES_H
