#include "materials.h"

map<string, std::pair<GLuint, int>> fileModels;

// GLuint vertices, verticeCount;

XMLElement * _getChildElement(XMLElement * elem, const char* name) {
    XMLElement * child;
    try {
        if (name == nullptr) {
            child = elem->FirstChildElement();
        } else {
            child = elem->FirstChildElement(name);
        }

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

vector<Transform *> Transform::parseTransform(XMLElement * transform) {
    
    vector<Transform *> transf;
            
    XMLElement * transform_child = _getChildElement(transform, nullptr);
    
    while (transform_child) {
        if (string(transform_child->Value()) == "translate") {
             transf.push_back(new Translate(transform_child));
        }
        else if (string(transform_child->Value()) == "rotate") {
             transf.push_back(new Rotate(transform_child));
        }   else if (string(transform_child->Value()) == "scale") {
             transf.push_back(new Scale(transform_child));
        } else {
            throw std::runtime_error("Invalid transformation '" + std::string(transform_child->Value()) + "'!");
        }
        transform_child = transform_child->NextSiblingElement();
    }
    
    return transf;
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
        vector<_3f> pts = GeometricShape::readFrom3DFile(fpath);
        vector<float> f_pts;
        for (_3f p : pts) {
            f_pts.push_back(p.x);
            f_pts.push_back(p.y);
            f_pts.push_back(p.z);
        }

        GLuint vbo;

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, f_pts.size() * sizeof(float), f_pts.data(), GL_STATIC_DRAW);
        
        fileModels[fpath] = make_pair(vbo, f_pts.size());
    }
    this->modelName = fpath;

    cout << "added a model " << endl;
}

void Model::run() {
    this->colour.run();
    //GeometricShape::drawObject(fileModels[this->modelName]);
    glBindBuffer(GL_ARRAY_BUFFER, fileModels[this->modelName].first);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    //glDrawElements(GL_TRIANGLES, fileModels[this->modelName].second, GL_UNSIGNED_INT, NULL);
    glDrawArrays(GL_TRIANGLES, 0, fileModels[this->modelName].second);
    cout << "did a model " << endl;
}


vector<Models *> Models::parseModels(XMLElement * models) {

    vector<Models *> ms;
    XMLElement * models_child = _getChildElement(models, nullptr);
    
    while (models_child) {
        if (string(models_child->Value()) == "model") {
             ms.push_back(new Model(models_child));
        }
        else {
            throw std::runtime_error("Invalid models element '" + std::string(models_child->Value()) + "'!");
        }
        models_child = models_child->NextSiblingElement();
    }
    
    return ms;
}

D3CircRandObjPlac::D3CircRandObjPlac(XMLElement * d3CircRandObjPlac) {
    this->radius = d3CircRandObjPlac->FloatAttribute("radius");
    this->num = d3CircRandObjPlac->IntAttribute("n");
    this->isRandRotation = d3CircRandObjPlac->BoolAttribute("isRandRotation");
    
    XMLElement * child = _getChildElement(d3CircRandObjPlac, "models");

    if (child) {
        vector<Models *> ms = Models::parseModels(child);
        for (auto m : ms)
            this->models.push_back(m);
    } else {
        throw std::runtime_error("Invalid d3CircRandObjPlac, modles element missing!");
    }

    for (int i = 0; i < this->num; i++) {
    float px = 0, pz = 0;
        while (pow(px, 2) + pow(pz, 2) < pow(radius, 2)) {
            float angle = 2.0 * M_PI * ((float)rand() / RAND_MAX);

            px = radius * cos(angle);
            pz = radius * sin(angle);
        }
        
        vector<Transform *> tfs;

        tfs.push_back(new Translate(px, 0, pz));

        if (this->isRandRotation) {
            float r_angle = 360.0 * ((double) rand() / RAND_MAX);
            tfs.push_back(new Rotate(r_angle, _3f(0, 1, 1)));
        }

        child = _getChildElement(d3CircRandObjPlac, "transform");
        if (child) {            
            vector <Transform *> additional_tfs = Transform::parseTransform(child);
            
            for (const auto t : additional_tfs) {
                tfs.push_back(t);
            }
        }

        this->transforms.push_back(tfs);
    }
}

void D3CircRandObjPlac::run() {
    for (const auto tfs : this->transforms) {
        glPushMatrix();

        for (const auto t : tfs) {
            t->run();
        }
        for (const auto m : this->models) {
            m->run();
        }
        glPopMatrix();
    }
}

Group::Group(XMLElement * group) {

    XMLElement * child = _getChildElement(group, nullptr);

    while (child) {
        string value = child->Value();
        if (value == "transform") {
            vector <Transform *> ts = Transform::parseTransform(child);
            for (auto t : ts)
                this->transformations.push_back(t);
        }
        else if (value == "models") {
            vector <Models *> ms = Models::parseModels(child);
            for (auto m : ms)
                this->models.push_back(m);
        }
        else if (value == "group") {
            this->groups.push_back(Group(child));
        } 
        else if (value == "d3CircRandObjPlac") {
            this->d3CircRandObjPlac.push_back(D3CircRandObjPlac(child));
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
    for (const auto transform : this->transformations) {
        transform->run();
    }

    for (const auto models : this->models) {
        models->run();
    }

    for (Group group : this->groups) {
        group.run();
    }

    for (D3CircRandObjPlac d3 : this->d3CircRandObjPlac) {
        d3.run();
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
}

void World::evaluateGroup(const string& path) {

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

    XMLElement * group = world->FirstChildElement("group");
    if (group) {
        this->group = Group(group);
    }

}
