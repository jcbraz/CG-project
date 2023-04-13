#include <vector>
#include "engineMaterials.h"

#include <iostream>
#include <string>
#include <vector>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#define GLUT_
#include "geometricShapes.h"

using namespace std;
using namespace tinyxml2;


Point::Point(float x, float y, float z) : x(x), y(y), z(z) {};

Window::Window(float w, float h) : width(w), height(h) {};

Camera::Camera(Point position, Point lookAt, Point up, Point projection) :
 position(position),
 lookAt(lookAt),
 up(up),
 projection(projection) {};

// Groups
void enterGroup() {
    glPushMatrix();
}
void leaveGroup() {
    glPopMatrix();
}

// Transforms
void applyTranslation(Point p) {
    glTranslatef(p.x, p.y, p.z);
}

void applyScale(Point p) {
    glScalef(p.x, p.y, p.z);
}

void applyRotation(float angle, Point p) {
    glRotatef(angle, p.x, p.y, p.z);
}

// Models
void drawModel(vector<Point> pts);

void applyXML(const string& filepath) {
    XMLDocument doc;
    try {
        XMLError read_error = doc.LoadFile(filepath.c_str());
        if (read_error != XML_SUCCESS) throw read_error;
    } catch (XMLError error) {
        cout << error << endl;
    }

    XMLNode* world;
    try {
        world = doc.FirstChild();
        if (world == nullptr) throw "Error finding element 'world'";
    } catch (const char* message) {
        cout << message << endl;
    }

    XMLElement* window;
    try {
        window = world->FirstChildElement("window");
        if (window == nullptr) {
            throw "Error finding element 'window'";
        }
    } catch (const char* message) {
        cout << message << endl;
    }

    int width = window->IntAttribute("width");
    int height = window->IntAttribute("height");

    XMLElement* camera;
    try {
        camera = world->FirstChildElement("camera");
        if (camera == nullptr) throw "Error finding element 'camera'";
    } catch (const char* message) {
        cout << message << endl;
    }

    XMLElement* position;
    try {
        position = camera->FirstChildElement("position");
        if (position == nullptr) throw "Error finding element 'position'";
    } catch (const char* message) {
        cout << message << endl;
    }
    int position_x = position->IntAttribute("x");
    int position_y = position->IntAttribute("y");
    int position_z = position->IntAttribute("z");

    XMLElement* lookAt;
    try {
        lookAt = camera->FirstChildElement("lookAt");
        if (lookAt == nullptr) throw "Error finding element 'lookAt'";
    } catch (const char* message) {
        cout << message << endl;
    }

    int lookAt_x = lookAt->IntAttribute("x");
    int lookAt_y = lookAt->IntAttribute("y");
    int lookAt_z = lookAt->IntAttribute("z");

    XMLElement* up;
    try {
        up = camera->FirstChildElement("up");
        if (up == nullptr) throw "Error finding element 'up'";
    } catch (const char* message) {
        cout << message << endl;
    }

    int up_x = up->IntAttribute("x");
    int up_y = up->IntAttribute("y");
    int up_z = up->IntAttribute("z");

    XMLElement* projection;
    try {
        projection = camera->FirstChildElement("projection");
        if (projection == nullptr) throw "Error finding element 'projection'";
    } catch (const char* message) {
        cout << message << endl;
    }

    float projection_fov = projection->FloatAttribute("fov");
    float projection_near = projection->FloatAttribute("near");
    float projection_far = projection->FloatAttribute("far");

    XMLElement* group = world->FirstChildElement("group");
    if (group) {
        parseGroup(group);
    }
}

void parseGroup(XMLElement* group) {
    enterGroup();
    XMLElement* transform = group->FirstChildElement("transform");
    if (transform) {
        XMLElement* translate = transform->FirstChildElement("translate");
        if (translate) {
            applyTranslation(Point(translate->FloatAttribute("x"),
                                   translate->FloatAttribute("y"),
                                   translate->FloatAttribute("z")));
        }
        XMLElement* rotate = transform->FirstChildElement("rotate");
        if (rotate) {
            applyRotation(
                rotate->FloatAttribute("angle"),
                Point(rotate->FloatAttribute("x"), rotate->FloatAttribute("y"),
                      rotate->FloatAttribute("z")));
        }
        XMLElement* scale = transform->FirstChildElement("scale");
        if (scale) {
            applyScale(Point(scale->FloatAttribute("x"),
                             scale->FloatAttribute("y"),
                             scale->FloatAttribute("z")));
        }
    }
    XMLElement* models = group->FirstChildElement("models");
    if (models) {
        XMLElement* model = models->FirstChildElement("model");
        if (model) {
            while (model) {
                string file = model->Attribute("file");
                vector<Point> modelPoints =
                    GeometricShape::readFrom3DFile(file);
                drawModel(modelPoints);
                model = model->NextSiblingElement("model");
            }
        }
    }
    XMLElement* groupChild = group->FirstChildElement("group");
    if (groupChild) {
        parseGroup(groupChild);
    } else if (group->NextSiblingElement("group")) {
        leaveGroup();
        parseGroup(group->NextSiblingElement("group"));
    } else {
        leaveGroup();
    }
}