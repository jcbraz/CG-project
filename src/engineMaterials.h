#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include "geometricShapes.h"


struct Transformations {
    vector<void *> transformations;
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

void enterGroup();
void leaveGroup();
void applyTranslation(Point p);
void applyScale(Point p);
void applyRotation(float angle, Point p);
void drawModel(std::vector<Point> pts);

#endif // ENGINE_H
