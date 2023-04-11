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
    World::transformation_map = map<string, vector<Transformation> >();
};

World::World(const Camera& camera, int width, int height,
             vector<string> files) {
    World::width = width;
    World::height = height;
    World::camera = Camera(camera);
    World::files = files;
    World::transformation_map = map<string, vector<Transformation> >();

    for (int i = 0; i < files.size(); i++) {
        World::transformation_map[files[i]] = vector<Transformation>();
    }
};

vector<string> World::handleFiles(XMLElement* element) {
    vector<string> repeated_files = vector<string>();

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
        // if the file key doesn't exist, create it
        if (!World::transformation_map.count(model->Attribute("file"))) {
            World::transformation_map[model->Attribute("file")] =
                vector<Transformation>();
        } else {
            // add to the vector of repeated files
            repeated_files.push_back(model->Attribute("file"));
        }

        model = model->NextSiblingElement();
    }

    return repeated_files;
}

void World::handleChainedTransformations(XMLElement* group) {
    // create buffers to store the transformations and repeated files
    vector<Transformation> transformations_buffer = vector<Transformation>();
    vector<string> repeated_files_buffer = World::handleFiles(group);

    XMLElement* transform = group->FirstChildElement("transform");
    if (transform) {
        Transformation new_transformation = Transformation();
        new_transformation.handleTransformation(transform);

        transformations_buffer.push_back(new_transformation);
        for (const auto& elem : World::transformation_map) {
            World::setTransformationsToFile(elem.first, transformations_buffer);
        }

        XMLElement* groupChild = group->FirstChildElement("group");
        if (groupChild != nullptr) {
            while (groupChild != nullptr) {
                repeated_files_buffer = World::handleFiles(groupChild);
                XMLElement* transformChild =
                    groupChild->FirstChildElement("transform");
                if (transformChild != nullptr) {
                    // create a new transformation based on the transform child
                    // node
                    Transformation transformationChild = Transformation();
                    transformationChild.handleTransformation(transformChild);
                    transformations_buffer.push_back(transformationChild);

                    for (const auto& elem : World::transformation_map) {
                        // check if the file is repeated or if it has no
                        // transformations
                        if (find(repeated_files_buffer.begin(),
                                 repeated_files_buffer.end(),
                                 elem.first) != repeated_files_buffer.end() ||
                            elem.second.size() == 0) {
                            // set the transformations list to the buffer with
                            // the chained transformations
                            World::setTransformationsToFile(
                                elem.first, transformations_buffer);
                        }
                    }
                }
                groupChild = groupChild->NextSiblingElement("group");
            }
        }
    }
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

    World::handleChainedTransformations(group);

    World::camera = Camera(position_x, position_y, position_z, lookAt_x,
                           lookAt_y, lookAt_z, up_x, up_y, up_z, projection_fov,
                           projection_near, projection_far);
    World::width = width;
    World::height = height;
    World::files = handleFiles(group);
}