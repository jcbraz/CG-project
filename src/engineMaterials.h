#ifndef ENGINE_H
#define ENGINE_H

#include <vector>

struct Point {
    float x;
    float y;
    float z;

    Point(float x, float y, float z);
};

class Window {
    private:
        float width;
        float height;

    public:
        Window(float width, float height);
        void setSize(float width, float height);
        float getWidth();
        float getHeight();
};

class Camera {
    private:
        Point position;
        Point lookAt;
        Point up;
        Point projection;

    public:
        Camera(Point position, Point lookAt, Point up, Point projection);
        void setPosition(Point position);
        Point getPosition();
        void setLookAt(Point lookAt);
        Point getLookAt();
        void setUp(Point up);
        Point getUp();
        void setProjection(Point projection);
        Point getProjection();
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
void displayFPS();

#endif // ENGINE_H
