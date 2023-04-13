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
}

void enterGroup();
void leaveGroup();
void translate(Point p);
void scale(Point p);
void rotate(float angle, Point p);
void drawModel(std::vector<Point> pts);

#endif // ENGINE_H
