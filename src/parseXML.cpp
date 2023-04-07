#include "parseXML.h"

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

/**
 * TRANSFORMATION SECTION
 */

Transformation Transformation::handleTransformation(XMLElement* element) {
    Transformation transformation;

    const XMLElement* translationElement =
        element->FirstChildElement("translation");
    if (translationElement != nullptr) {
        transformation.addTranslation(translationElement->FloatAttribute("x"),
                                      translationElement->FloatAttribute("y"),
                                      translationElement->FloatAttribute("z"));
    }

    const XMLElement* rotationElement = element->FirstChildElement("rotation");
    if (rotationElement != nullptr) {
        transformation.addRotation(rotationElement->FloatAttribute("angle"),
                                   rotationElement->FloatAttribute("x"),
                                   rotationElement->FloatAttribute("y"),
                                   rotationElement->FloatAttribute("z"));
    }

    const XMLElement* scaleElement = element->FirstChildElement("scale");
    if (scaleElement != nullptr) {
        transformation.addScale(scaleElement->FloatAttribute("x"),
                                scaleElement->FloatAttribute("y"),
                                scaleElement->FloatAttribute("z"));
    }

    return transformation;
}

/*
 * WORLD SECTION
 */

World::World() {
    World::camera = Camera();
    World::files = vector<string>(2);
    World::transformation_chain = vector<TransformationsPerFile>();
};

World::World(int width, int height, vector<string> files) {
    World::camera = Camera();
    World::files = files;
    World::transformation_chain = vector<TransformationsPerFile>();
};

World::World(const Camera& camera, int width, int height,
             vector<string> files) {
    World::width = width;
    World::height = height;
    World::camera = Camera(camera);
    World::files = files;
    World::transformation_chain = vector<TransformationsPerFile>();
};

vector<string> World::handleFiles(XMLElement* element) {
    vector<string> files;
    XMLElement* models;

    try {
        models = element->FirstChildElement("models");
        if (models == nullptr) throw "Error finding element 'models'";
    } catch (const char* message) {
        cout << message << endl;
    }

    XMLElement* model;
    try {
        model = models->FirstChildElement();
        if (model == nullptr) throw "Error finding element 'model'";
    } catch (const char* message) {
        cout << message << endl;
    }

    while (model != nullptr) {
        files.push_back(model->Attribute("file"));
        model = model->NextSiblingElement();
    }

    try {
        if (files.size() == 0) throw "No models found";
    } catch (const char* message) {
        cout << message << endl;
    }

    return files;
}

TransformationsPerFile World::generateTransformationPerFile(
    Transformation transformation, vector<string> files) {
    TransformationsPerFile transformationsPerFile;
    transformationsPerFile.transformations = transformation;
    transformationsPerFile.files = files;

    return transformationsPerFile;
};

vector<TransformationsPerFile> World::handleChainedTransformations(
    Transformation transformation, vector<string> files, XMLElement* transform,
    XMLElement* group) {
    vector<TransformationsPerFile> transformationsPerFile =
        vector<TransformationsPerFile>();

    Transformation transformationData = Transformation();
    TransformationsPerFile tpf = generateTransformationPerFile(
        transformationData.handleTransformation(transform), files);
    transformationsPerFile.push_back(tpf);

    XMLElement* groupChild = group->FirstChildElement("group");
    if (groupChild != nullptr) {
        while (groupChild != nullptr) {
            XMLElement* transformChild =
                groupChild->FirstChildElement("transform");
            if (transformChild != nullptr) {
                Transformation transformationChild = Transformation();

                Transformation handledTransformation =
                    transformationChild.handleTransformation(transformChild);
                vector<string> filesChild = handleFiles(groupChild);
                TransformationsPerFile tpf_child =
                    generateTransformationPerFile(handledTransformation,
                                                  filesChild);
                transformationsPerFile.push_back(tpf_child);
            }
            groupChild = groupChild->FirstChildElement("group");
        }
    }

    return transformationsPerFile;
}

World::World(const string& filepath) {
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

    XMLElement* group;
    try {
        group = world->FirstChildElement("group");
        if (group == nullptr) throw "Error finding element 'group'";
    } catch (const char* message) {
        cout << message << endl;
    }

    XMLElement* transform;
    try {
        transform = group->FirstChildElement("transform");
        if (transform == nullptr) throw "Error finding element 'transform'";
    } catch (const char* message) {
        cout << message << endl;
    }


    
    vector<string> filesXML = handleFiles(group);

    World::transformation_chain = World::handleChainedTransformations(
        Transformation(), filesXML, transform, group);

    World::camera = Camera(position_x, position_y, position_z, lookAt_x,
                           lookAt_y, lookAt_z, up_x, up_y, up_z, projection_fov,
                           projection_near, projection_far);
    World::width = width;
    World::height = height;
    World::files = filesXML;
}

// XMLElement* models;
// try {
//     models = group->FirstChildElement("models");
//     if (models == nullptr) throw "Error finding element 'models'";
// } catch (const char* message) {
//     cout << message << endl;
// }

// vector<string> files;

// XMLElement* model;
// try {
//     model = models->FirstChildElement();
//     if (model == nullptr) throw "Error finding element 'model'";
// } catch (const char* message) {
//     cout << message << endl;
// }

// while (model != nullptr) {
//     files.push_back(model->Attribute("file"));
//     model = model->NextSiblingElement();
// }

// try {
//     if (files.size() == 0) throw "No models found";
// } catch (const char* message) {
//     cout << message << endl;
// }