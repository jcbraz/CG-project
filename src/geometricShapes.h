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

struct Point {
    float x;
    float y;
    float z;

public:
    Point();
    Point(float x, float y, float z);
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
    virtual vector<Point> getPoints() = 0;

    static void drawObject(vector<Point> points);

    static void writeTo3DFile(vector<Point> points, string fName);

    static vector<Point> readFrom3DFile(string fName);

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
        vector<Point> getPoints() override;

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
        vector<Point> getPoints() override;

    protected:
        void Print(ostream &) const override;};

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
    vector<Point> getPoints() override;

protected:
    void Print(ostream &) const override;};

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
        vector<Point> getPoints() override;

    protected:
        void Print(ostream &) const override;};
/*
 *
 * END SPHERE CLASS
 *
 */

#endif //GROUP_PROJECT_GEOMETRICSHAPES_H