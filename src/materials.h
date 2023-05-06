#ifndef MATERIALS_H
#define MATERIALS_H

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include<math.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <tinyxml2.h>

#include "geometricShapes.h"
#include "splines.h"

using namespace std;
using namespace tinyxml2;

enum MTValue {
    MT_CODE_COLOUR_DRAW
};

void mtEnable(MTValue v);
void mtDisable(MTValue v);


class Window {
    private: 
        int width;
        int height;
    
    public:
        Window() : width(800), height(800) {};
        Window (int width, int height) : width(width), height(height) {};
        explicit Window (XMLElement * window);
        float getWidth() const { return width; };
        float getHeight() const { return height; };
};

class Camera {
    private:
        _3f position;
        _3f lookAt;
        _3f up;
        _3f projection;

    public:
        Camera() : 
        position(_3f(60, 60, 10)),
        lookAt(_3f(0,0,0)),
        up(_3f(0,1,0)),
        projection(_3f(60, 1, 1000)) {};

        Camera(_3f position, _3f lookAt, _3f up, _3f projection) :
        position(position),
        lookAt(lookAt),
        up(up),
        projection(projection) {};

        explicit Camera(XMLElement * camera);

        void setPosition(_3f position) { Camera::position = position; };
        _3f getPosition() { return position; };
        void setLookAt(_3f lookAt) { Camera::lookAt = lookAt; };
        _3f getLookAt() { return lookAt; };
        void setUp(_3f up) { Camera::up = up; };
        _3f getUp() { return up; };
        void setProjection(_3f projection) { Camera::projection = projection; };
        _3f getProjection() { return projection; };

};

class Transform {
    public:
        virtual ~Transform() = default;
        virtual void run() = 0;
        static vector<Transform *> parseTransform(XMLElement * transform);
};

class Rotate : public Transform {
    private:
    float angle;
    _3f p;
    float t;
    float time;
    

    public:
        explicit Rotate(XMLElement * rotate);
        Rotate(float angle, _3f p) : angle(angle), p(p), t(0), time(0)  {}
        void run() override;
};


class Translate : public Transform {
    private:
        _3f p;
        vector<_3f> catmullPoints; 
        float t;
        float time;
        bool isAlign;
        _3f prev_y;
    
    public:
        explicit Translate(XMLElement * translate);
        Translate(float x, float y, float z) : p(_3f(x, y, z)) {};
        void run() override;
};


class Scale : public Transform {
    private:
        _3f p;
    
    public:
        explicit Scale(XMLElement * scale);
        explicit Scale(_3f p) : p(p) {};
        void run() override;
};

class Colour {
    private:
        _3f colour;
        GLfloat * diffuse;
        GLfloat * ambient;
        GLfloat * specular;
        GLfloat * emissive;
        float shininess;
        bool hasColour;

    public:
        Colour() { colour = _3f(1.0f, 1.0f, 1.0f); };
        explicit Colour(XMLElement * colour);
        void run();
};

class Text {
    private:
        string content;
        float x;
        float y;
        Colour colour;

    public:
        Text(XMLElement * text);
        void run();
};


class Models {
    public:
        virtual ~Models() = default;
        virtual void run() = 0;
        static vector <Models *> parseModels(XMLElement * models);
};


class D3CircRandObjPlac {
    private:
        float radius;
        int num;
        bool isRandRotation;
        vector<Models *> models;
        vector<vector<Transform *> > transforms;

    public:
        D3CircRandObjPlac(XMLElement * d3CircRandObjPlac);
        void run();
};


class Group {
    public:
        vector<Models*> models;
        vector<Transform*> transformations;
        vector<D3CircRandObjPlac> d3CircRandObjPlac;
        vector<Text> texts;
        vector<Group> groups;

    public:
        Group() = default;
        Group(XMLElement * group);
        void run();
};

class Event {
    private:
        unsigned int code;
        Group group;

    public:
        Event() = default;
        Event(XMLElement * event, unsigned int code);
        //Event(XMLElement * event);
        int get() {return code;};
        void run();
};


class Model : public Models {
    private:
        unsigned int code;
        string modelName;
        Colour colour;
        bool disableCull;
        Event event;
    
    public:
        explicit Model(XMLElement * model);
        void run() override;
};

class Light {
    public:
        virtual ~Light() = default;
        virtual void run(GLuint light) = 0;
};

class DirectionalLight : public Light {
    private:
        GLfloat direction[4];
    public:
        DirectionalLight(XMLElement  * directionalLight);
        void run(GLuint light) override;
};

class PointLight : public Light {
    private:
        GLfloat position[4];
    public:
        PointLight(XMLElement * pointLight);
        void run(GLuint light) override;
};

class SpotLight : public Light {
    private:
        GLfloat point[4];
        GLfloat direction[4];
        float cutoff;
    public:
        SpotLight(XMLElement * spotLight);
        void run(GLuint light) override;
};

class Lights {
    private:
        vector<Light *> lights;
    public:
        Lights() = default;
        Lights(XMLElement * lights);
        void run();
};

class World {
    private:
        Window window;
        Camera camera;
        Lights lights;
        Group group;
    
    public:
        explicit World(const string& path);
        void evaluateGroup(const string& path);
        Camera getCamera() {return camera;};
        Window getWindow() {return window;};
        Group getGroup() {return group;};
        Lights getLights() {return lights;};
};


int picking(int x, int y, Camera * c, Group * g);

#endif

