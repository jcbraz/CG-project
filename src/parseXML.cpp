#include "parseXML.h"

pair<World*, Content*> parseWorld(const string& filepath) {
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

    Content* content = new Content();

    if (group) {
        parseGroup(group, content);
    }

    return make_pair(
        new World(
            Window(width, height),
            Camera(Point(position_x, position_y, position_z),
                   Point(lookAt_x, lookAt_y, lookAt_z), Point(up_x, up_y, up_z),
                   Point(projection_fov, projection_near, projection_far))),
        content);
}






void _parse_color(XMLElement * color, Content * content) {
    if (color) {
        content->insert_COLOR(Point(color->FloatAttribute("r"),
                            color->FloatAttribute("g"),
                            color->FloatAttribute("b")));
    } else {
        content->insert_COLOR(Point(1.0f, 1.0f, 1.0f));
    }
}

void _parse_3dCircRandObjPlac(XMLElement * _3dCircRandObjPlac, Content * content) {
    Point c = Point(1.0f, 1.0f, 1.0f);

    XMLElement* models = _3dCircRandObjPlac->FirstChildElement("models");
    if (models) {

        XMLElement* model = models->FirstChildElement("model");
        if (model) {
            while (model) {
                XMLElement* color = model->FirstChildElement("color");
                
                _parse_color(color, content);
                
                const XMLAttribute * at_scaleX = _3dCircRandObjPlac->FindAttribute("scaleX");
                float scale_X;
                if (at_scaleX)
                    scale_X = _3dCircRandObjPlac->FloatAttribute("scaleX");
                else
                    scale_X = 1;

                const XMLAttribute * at_scaleY = _3dCircRandObjPlac->FindAttribute("scaleY"); 
               float scale_Y;
                if (at_scaleY)
                    scale_Y = _3dCircRandObjPlac->FloatAttribute("scaleY");
                else
                    scale_Y = 1;

                const XMLAttribute * at_scaleZ = _3dCircRandObjPlac->FindAttribute("scaleZ");   
                float scale_Z;
                if (at_scaleZ)
                    scale_Z = _3dCircRandObjPlac->FloatAttribute("scaleZ");
                else
                    scale_Z = 1;

                const XMLAttribute * at_isRandRotation = _3dCircRandObjPlac->FindAttribute("isRandRotation");
                bool isRandRotation = false;
                if (at_isRandRotation) {
                    isRandRotation = _3dCircRandObjPlac->BoolAttribute("isRandRotation");
                }

                content->insert_3D_CIRC_RAND_OBJ_PLACEMENT(
                    _3dCircRandObjPlac->FloatAttribute("radius"),
                    isRandRotation,
                    _3dCircRandObjPlac->IntAttribute("n"),
                    Point(scale_X, scale_Y, scale_Z),
                    model->Attribute("file")
                );
                model = model->NextSiblingElement("model");
            }
        }
    } else {
        throw "Models missing in 3dCircRandObjPlac!";
    }

}

void _parse_model(XMLElement * model, Content * content) {
    XMLElement* color = model->FirstChildElement("color");
    _parse_color(color, content);

    const XMLAttribute * at_disableCull = model->FindAttribute("disableCull");
    bool disableCull = false;
    if (at_disableCull) {
        disableCull = model->BoolAttribute("disableCull");
    }


    if (disableCull)
        content->insert_DISABLE_CULL();

    content->insert_MODEL(model->Attribute("file"));

    if (disableCull)
        content->insert_ENABLE_CULL();
}

void _parse_models(XMLElement * models, Content * content) {
    XMLElement* model = models->FirstChildElement("model");
    while (model) {
        _parse_model(model, content);
        model = model->NextSiblingElement("model");
    }
}




void parseGroup(XMLElement* group, Content* content) {
    content->insert_PUSH_MATRIX();

    XMLElement* transform = group->FirstChildElement("transform");
    if (transform) {
        XMLElement* transformChildren = transform->FirstChildElement();
        if (transformChildren) {
            while (transformChildren) {
                if (transformChildren->Value() == string("translate")) {
                    content->insert_TRANSLATE(
                        Point(transformChildren->FloatAttribute("x"),
                              transformChildren->FloatAttribute("y"),
                              transformChildren->FloatAttribute("z")));
                    transformChildren = transformChildren->NextSiblingElement();
                } else if (transformChildren->Value() == string("rotate")) {
                    content->insert_ROTATE(
                        transformChildren->FloatAttribute("angle"),
                        Point(transformChildren->FloatAttribute("x"),
                              transformChildren->FloatAttribute("y"),
                              transformChildren->FloatAttribute("z")));
                    transformChildren = transformChildren->NextSiblingElement();
                } else if (transformChildren->Value() == string("scale")) {
                    content->insert_SCALE(
                        Point(transformChildren->FloatAttribute("x"),
                              transformChildren->FloatAttribute("y"),
                              transformChildren->FloatAttribute("z")));
                    transformChildren = transformChildren->NextSiblingElement();
                } else {
                    cout << "Invalid transformation given" << endl;
                    transformChildren = transformChildren->NextSiblingElement();
                }
            }
        }
    }

    XMLElement* _3dCircRandObjPlac = group->FirstChildElement("d3CircRandObjPlac");
    while (_3dCircRandObjPlac) {
        _parse_3dCircRandObjPlac(_3dCircRandObjPlac, content);
        _3dCircRandObjPlac = _3dCircRandObjPlac->NextSiblingElement("d3CircRandObjPlac");
    }
    
    XMLElement* models = group->FirstChildElement("models");
    if (models) {
        _parse_models(models, content);
    }
    XMLElement* groupChild = group->FirstChildElement("group");
    if (groupChild) {
        parseGroup(groupChild, content);
    }

    if (group->NextSiblingElement("group")) {
        content->insert_POP_MATRIX();
        parseGroup(group->NextSiblingElement("group"), content);
    } else {
        content->insert_POP_MATRIX();
    }
}

