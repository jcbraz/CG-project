#include "parseXML.h"

#include <tinyxml2.h>

using namespace std;
using namespace tinyxml2;

/*
 * CAMERA SECTION
 */

Camera::Camera() {
    Camera::position.x = 3;
    Camera::position.y = 2;
    Camera::position.z = 1;

    Camera::lookAt.x = 0;
    Camera::lookAt.y = 0;
    Camera::lookAt.z = 0;

    Camera::up.x = 0;
    Camera::up.y = 1;
    Camera::up.z = 0;

    Camera::projection.fov = 60;
    Camera::projection.near = 1;
    Camera::projection.far = 1000;
}

Camera::Camera(const Camera& camera) {
    Camera::position = camera.position;
    Camera::lookAt = camera.lookAt;
    Camera::up = camera.up;
    Camera::projection = camera.projection;
}

Camera::Camera(Position position, LookAt lookAt, Up up, Projection projection) {
    Camera::position = position;
    Camera::lookAt = lookAt;
    Camera::up = up;
    Camera::projection = projection;
};

Camera::Camera(int position_x, int position_y, int position_z, int lookAt_x,
               int lookAt_y, int lookAt_z, int up_x, int up_y, int up_z,
               float projection_fov, float projection_near,
               float projection_far) {
    Camera::position.x = position_x;
    Camera::position.y = position_y;
    Camera::position.z = position_z;

    Camera::lookAt.x = lookAt_x;
    Camera::lookAt.y = lookAt_y;
    Camera::lookAt.z = lookAt_z;

    Camera::up.x = up_x;
    Camera::up.y = up_y;
    Camera::up.z = up_z;

    Camera::projection.fov = projection_fov;
    Camera::projection.near = projection_near;
    Camera::projection.far = projection_far;
};

/*
 * WORLD SECTION
 */

World::World() {
    World::camera = Camera();
    World::files = vector<string>(2);
};

World::World(int width, int height, vector<string> files) {
    World::camera = Camera();
    World::files = files;
};

World::World(const Camera& camera, int width, int height, vector<string> files) {
    World::width = width;
    World::height = height;
    World::camera = Camera(camera);
    World::files = files;
};

World* parseXML(const string& filepath) {
    XMLDocument xml_doc;

    try {
        XMLError read_result = xml_doc.LoadFile(filepath.c_str());
        if (read_result != XML_SUCCESS) throw read_result;
    } catch (XMLError read_result) {
        cout << "Error loading XML file: " << read_result << endl;
    }

    XMLNode* world;
    try {
        world = xml_doc.FirstChild();
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
        
    }

    int width = window->IntAttribute("width");
    int height = window->IntAttribute("height");

    XMLElement* camera;
    try {
        camera = world->FirstChildElement("camera");
        if (camera == nullptr) throw "Error finding element 'camera'";
    } catch (const char* message) {
        
    }

    int position_x = camera->IntAttribute("x");
    int position_y = camera->IntAttribute("y");
    int position_z = camera->IntAttribute("z");

    XMLElement* lookAt;
    try {
        lookAt = camera->FirstChildElement("lookAt");
        if (lookAt == nullptr) throw "Error finding element 'lookAt'";
    } catch (const char* message) {
        
    }

    int lookAt_x = lookAt->IntAttribute("x");
    int lookAt_y = lookAt->IntAttribute("y");
    int lookAt_z = lookAt->IntAttribute("z");

    XMLElement* up;
    try {
        up = camera->FirstChildElement("up");
        if (up == nullptr) throw "Error finding element 'up'";
    } catch (const char* message) {
        
    }

    int up_x = up->IntAttribute("x");
    int up_y = up->IntAttribute("y");
    int up_z = up->IntAttribute("z");

    XMLElement* projection;
    try {
        projection = camera->FirstChildElement("projection");
        if (projection == nullptr) throw "Error finding element 'projection'";
    } catch (const char* message) {
        
    }

    int projection_fov = projection->IntAttribute("fov");
    int projection_near = projection->IntAttribute("near");
    int projection_far = projection->IntAttribute("far");

    XMLElement* group;
    try {
        group = world->FirstChildElement("group");
        if (group == nullptr) throw "Error finding element 'group'";
    } catch (const char* message) {
        
    }

    XMLElement* models;
    try {
        models = group->FirstChildElement("models");
        if (models == nullptr) throw "Error finding element 'models'";
    } catch (const char* message) {
        
    }

    vector<string> files = vector<string>(1);

    XMLElement* model;
    try {
        model = models->FirstChildElement();
        if (model == nullptr) throw "Error finding element 'model'";
    } catch (const char* message) {
        
    }

    while (model != nullptr) {
        files.push_back(model->Attribute("file"));
        model = model->NextSiblingElement();
    }

    try {
        if (files.size() == 0) throw "No models found";
    } catch (const char* message) {
        
    }
    
    Camera* cameraForFinalConstructor = new Camera(
        position_x, position_y, position_z, lookAt_x, lookAt_y, lookAt_z, up_x,
        up_y, up_z, projection_fov, projection_near, projection_far);


    World* finalWorld = new World(*cameraForFinalConstructor, width, height, files);

    return finalWorld;
}

int main() {
    World* world = parseXML("file.xml");
    std::vector<std::string> fic = world->files;
    for (int i = 0; i < fic.size(); i++) {
        std::cout << fic[i] << std::endl;
    }
    delete world;
    return 0;
}