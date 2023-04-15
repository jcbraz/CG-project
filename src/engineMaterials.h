#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <map>
#include "geometricShapes.h"

using namespace std;

enum Action {
    AC_PUSH_MATRIX,
    AC_POP_MATRIX,
    AC_TRANSLATE,
    AC_ROTATE,
    AC_SCALE,
    AC_MODEL,
    AC_COLOR,
    AC_3D_CIRC_RAND_OBJ_PLACEMENT,
    AC_DISABLE_CULL,
    AC_ENABLE_CULL
    };

class Content {
    private:
        vector<Action> actions;
        vector<float> arguments;
        vector<string> i_models;
        map<string, vector<Point>> models;
        //vector<vector<Point>> models;

    public:
        Content();
        void insert_PUSH_MATRIX();
        void insert_POP_MATRIX();
        void insert_TRANSLATE(Point p);
        void insert_ROTATE(float angle, Point p);
        void insert_SCALE(Point p);
        void insert_MODEL(const string& filepath);
        void insert_COLOR(Point p);
        void insert_3D_CIRC_RAND_OBJ_PLACEMENT(float radius, bool isRandRotation, int n, Point scale, const string& filepath);
        void insert_DISABLE_CULL();
        void insert_ENABLE_CULL();
        void applyContent();
};

class Window {
    private:
        float width;
        float height;

    public:
        Window(float width, float height);
        void setSize(float width, float height);
        float getWidth() { return width; };
        float getHeight() { return height; };
};

class Camera {
    private:
        Point position;
        Point lookAt;
        Point up;
        Point projection;

    public:
        Camera(Point position, Point lookAt, Point up, Point projection);
        void setPosition(Point position) { Camera::position = position; };
        Point getPosition() { return position; };
        void setLookAt(Point lookAt) { Camera::lookAt = lookAt; };
        Point getLookAt() { return lookAt; };
        void setUp(Point up) { Camera::up = up; };
        Point getUp() {return up; };
        void setProjection(Point projection) { Camera::projection = projection; };
        Point getProjection() { return projection; };
};

class World {
    private:
        Window window;
        Camera camera;
    public:
        World(Window w, Camera c);
        Window getWindow() { return window; };
        Camera getCamera() {return camera; };
};

#endif // ENGINE_H
