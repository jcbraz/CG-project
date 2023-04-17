#include "materials.h"

map<string, vector<_3f>> fileModels;

XMLElement * _getChildElement(XMLElement * elem, const char* name) {
    XMLElement * child = nullptr;

    try {
        if (name == nullptr) {
            child = elem->FirstChildElement();
        } else {
            child = elem->FirstChildElement(name);
        }
        if (!child)
            return nullptr;

    } catch (const char * message) {
        cout << message << endl;
    }
    
    return child;
}


Window::Window(XMLElement * window) {
    this->width = window->IntAttribute("width");
    this->height = window->IntAttribute("height");
}

Camera::Camera(XMLElement * camera) {
    
    XMLElement * pos = _getChildElement(camera, "position");

    this->position = _3f(
        pos->FloatAttribute("x"),
        pos->FloatAttribute("y"),
        pos->FloatAttribute("z")
    );

    XMLElement * lat = _getChildElement(camera, "lookAt");

    this->lookAt = _3f(
        lat->FloatAttribute("x"),
        lat->FloatAttribute("y"),
        lat->FloatAttribute("z")
    );

    XMLElement * _up = _getChildElement(camera, "up");

    this->up = _3f(
        _up->FloatAttribute("x"),
        _up->FloatAttribute("y"),
        _up->FloatAttribute("z")  
    );

    XMLElement * proj = _getChildElement(camera, "projection");

    this->projection = _3f(
        proj->FloatAttribute("fov"),
        proj->FloatAttribute("near"),
        proj->FloatAttribute("far")
    );
}

Rotate::Rotate(XMLElement * rotate) {
    this->angle = rotate->FloatAttribute("angle");
    this->p = _3f(
        rotate->FloatAttribute("x"),
        rotate->FloatAttribute("y"),
        rotate->FloatAttribute("z")
    );

    cout << "added a rotate " << endl;

}

void Rotate::run() {
    glRotatef(this->angle, this->p.x, this->p.y, this->p.z);
    cout << "did a rotate " << endl;
}

Translate::Translate(XMLElement * translate) {
    this->p = _3f(
        translate->FloatAttribute("x"),
        translate->FloatAttribute("y"),
        translate->FloatAttribute("z")
    );

        cout << "added a translate " << this->p.x << this->p.y << this->p.z << endl;

}

void Translate::run() {
    glTranslatef(this->p.x, this->p.y, this->p.z);
    cout << "did a translate " << endl;
}

Scale::Scale(XMLElement * scale) {
    this->p = _3f(
        scale->FloatAttribute("x"),
        scale->FloatAttribute("y"),
        scale->FloatAttribute("z")
    );
    
    cout << "added a scale " << endl;
}


void Scale::run() {
    glScalef(this->p.x, this->p.y, this->p.z);

    cout << "did a scale " << endl;
}

Colour::Colour(XMLElement * colour) {
    if (!colour) {
        this->p = _3f(1, 1, 1);
    } else {
        this->p = _3f(
            colour->FloatAttribute("r"),
            colour->FloatAttribute("g"),
            colour->FloatAttribute("b")
        );

        cout << "added a colour " << endl;
    }
}

void Colour::run() {
    glColor3f(this->p.x, this->p.y, this->p.z);
}

Model::Model(XMLElement * model) : disableCull(false) {
    XMLElement * colour = model->FirstChildElement("color");
    this->colour = Colour(colour);

    const XMLAttribute * at_disableCull = model->FindAttribute("disableCull");

    if (at_disableCull)
        this->disableCull = model->BoolAttribute("disableCull");

    string fpath = model->Attribute("file");
    if (fileModels.find(fpath) == fileModels.end()) {
        fileModels[fpath] =  GeometricShape::readFrom3DFile(fpath);
    }

    this->modelName = fpath;

    cout << "added a model " << endl;
}

void Model::run() {
    glBegin(GL_TRIANGLES);
    this->colour.run();
    GeometricShape::drawObject(fileModels[this->modelName]);
    cout << "did a model " << endl;
}

Models::Models(XMLElement * models) {
    XMLElement * child = _getChildElement(models, nullptr);

    while(child) {
        if (string(child->Value()) == "model") {
            this->models.push_back(Model(child));
        } else {
        throw std::runtime_error("Invalid models child '" + std::string(child->Value()) + "'!");
        }
        child = child->NextSiblingElement();
    }

    cout << "added a models " << endl;
}

void Models::run() {
    for (auto model : models) {
        model.run();
    }
}

/*
D3CircRandObjPlac::D3CircRandObjPlac(XMLElement * d3CircRandObjPlac) {
    this->radius = d3CircRandObjPlac->FloatAttribute("radius");
    this->num = d3CircRandObjPlac->IntAttribute("n");
    this->isRandRotation = d3CircRandObjPlac->BoolAttribute("isRandRotation");
    this->scale = Scale(_3f(
            d3CircRandObjPlac->FloatAttribute("scaleX"),
            d3CircRandObjPlac->FloatAttribute("scaleY"),
            d3CircRandObjPlac->FloatAttribute("scaleZ")
            ));
}*/

Group::Group(XMLElement * group) {

    XMLElement * child = _getChildElement(group, nullptr);

    while (child) {
        if (string(child->Value()) == "transform") {

            XMLElement * transform_child = _getChildElement(child, nullptr);

            while (transform_child) {

                if (string(transform_child->Value()) == "translate") {
                    this->transformations.push_back(new Translate(transform_child));
                }

                else if (string(transform_child->Value()) == "rotate") {
                    this->transformations.push_back(new Rotate(transform_child));
                }   else if (string(transform_child->Value()) == "scale") {
                    this->transformations.push_back(new Scale(transform_child));
                } else {
                    throw std::runtime_error("Invalid transformation '" + std::string(transform_child->Value()) + "'!");
                }
                transform_child = transform_child->NextSiblingElement();
            }
        }
        else if (string(child->Value()) == "models") {
            this->models.push_back(Models(child));
        }
        else if (string(child->Value()) == "group") {
            this->groups.push_back(Group(child));
        }
        else {
            throw std::runtime_error("Invalid group child value '" + std::string(child->Value()) + "'!");
        }

        child = child->NextSiblingElement();
    }
    cout << "added a group " << endl;
}

void Group::run() {
    glPushMatrix();
    for (auto transform : this->transformations) {
        transform->run();
    }

    for (auto models : this->models) {
        models.run();
    }

    for (Group group : this->groups) {
        group.run();
    }

    glPopMatrix();
}

World::World(const string& path) {
    XMLDocument doc;

    try {
        XMLError read_error = doc.LoadFile(path.c_str());
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

    XMLElement * window;
    try {
        window = world->FirstChildElement("window");
        if (window == nullptr) {
            throw "Error finding element 'window'";
        }
    } catch (const char* message) {
        cout << message << endl;
    }

    this->window = Window(window);

    XMLElement* camera;
    try {
        camera = world->FirstChildElement("camera");
        if (camera == nullptr) throw "Error finding element 'camera'";
    } catch (const char* message) {
        cout << message << endl;
    }
    this->camera = Camera(camera);

    XMLElement * group = world->FirstChildElement("group");

    if (group) {
        this->group = Group(group);
    }
}
