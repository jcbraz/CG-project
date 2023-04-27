#include "materials.h"
#include <cmath>
//                            VBO   PRIMITIVE  N_PTS
map<string, vector<std::tuple<GLuint, int, int>>> fileModels;

unsigned int picked;

bool mt_drawCodeColour = false;

int w = 0, h = 0;

void mtEnable(MTValue v) {
    switch(v) {
        case MT_CODE_COLOUR_DRAW:
            mt_drawCodeColour = true;
            break;
        default:
            throw "Invalid MTValue!";
            break;
    }
}

void mtDisable(MTValue v) {
    switch(v) {
        case MT_CODE_COLOUR_DRAW:
            mt_drawCodeColour = false;
            break;
        default:
            throw "Invalid MTValue!";
            break;
    }
}


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


Event::Event(XMLElement * event, unsigned int code) {
    this->code = code;

    XMLElement * group = _getChildElement(event, "group");
    if (group) 
        this->group = Group(group);
}

void Event::run() {
    if (picked == this->code)
        group.run();
}

unsigned int * _availableCodes = (unsigned int*) calloc(254, sizeof(unsigned int));

int _getNextAvailableCode() {
    for (int i = 1; i < 255; i++) {
        if (_availableCodes[i-1] == 0) {
            return i;
        }
    }
    throw "No more codes available!!";
    return -1;
}

void _setUnavailableCode(unsigned int code) {
    _availableCodes[code-1] = code;
}

int picking(int xx, int yy, Camera * camera, Group * group) {    
	// Turn off lighting and texturing
	//glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// Clear the frame buffer and place the camera
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
    _3f p = camera->getPosition();
    _3f l = camera->getLookAt();
    _3f u = camera->getUp();
	gluLookAt(p.x, p.y, p.z, 
		      l.x, l.y, l.z,
			  u.x, u.y, u.z);
	
	// Draw coded version of objects taking advantage of the values stored on the depth buffer
	glDepthFunc(GL_LEQUAL);
		// draw
        mtEnable(MT_CODE_COLOUR_DRAW);  
        group->run();
        mtDisable(MT_CODE_COLOUR_DRAW);      
	glDepthFunc(GL_LESS);

    // Read pixel under mouse position	
    GLint viewport[4];
    unsigned char res[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    glReadPixels(xx,viewport[3] - yy,1,1, GL_RGBA,GL_UNSIGNED_BYTE, res);

	// Reactivate lighting and texturing
	//glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

    if (picked)
        cout << "entrei picked: "<< picked << endl;

    picked = res[0];
	// Return red color component
	return res[0]; 
}

Window::Window(XMLElement * window) {
    this->width = window->IntAttribute("width");
    this->height = window->IntAttribute("height");
    h = this->height;
    w = this->width;
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
}

void Rotate::run() {
    glRotatef(this->angle, this->p.x, this->p.y, this->p.z);
}

Translate::Translate(XMLElement * translate) {
    this->p = _3f(
        translate->FloatAttribute("x"),
        translate->FloatAttribute("y"),
        translate->FloatAttribute("z")
    );
}

void Translate::run() {
    glTranslatef(this->p.x, this->p.y, this->p.z);
}

Scale::Scale(XMLElement * scale) {
    this->p = _3f(
        scale->FloatAttribute("x"),
        scale->FloatAttribute("y"),
        scale->FloatAttribute("z")
    );
    
}


void Scale::run() {
    glScalef(this->p.x, this->p.y, this->p.z);

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

Text::Text(XMLElement * text) {
    this->content = text->Attribute("content");
    this->x = text->FloatAttribute("x");
    this->y = text->FloatAttribute("y");

    XMLElement * colour = _getChildElement(text, "colour");
    this->colour = Colour(colour);
}

void Text::run() {

    this->colour.run();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, w, h, 0);
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_DEPTH_TEST);
    //glDisable(GL_LIGHTING);

    glPushMatrix();
    glLoadIdentity();
    glRasterPos2d(this->x, this->y);

    for (const char * c = this->content.c_str(); *c; c++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_LIGHTING)
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
    }
}

void Colour::run() {
    glColor3f(this->p.x, this->p.y, this->p.z);
}

Model::Model(XMLElement * model) : disableCull(false), code(0) {

    XMLElement * colour = model->FirstChildElement("color");
    this->colour = Colour(colour);

    const XMLAttribute * at_disableCull = model->FindAttribute("disableCull");

    if (at_disableCull)
        this->disableCull = model->BoolAttribute("disableCull");

    const XMLAttribute * at_code = model->FindAttribute("code");

    if(at_code) {
        this->code = model->IntAttribute("code");
    }
    XMLElement * event = _getChildElement(model, "event");

    if (event) {
        if (this->code > 0) {
            this->event = Event(event, this->code);
        } else {
            unsigned int code = _getNextAvailableCode();
            this->code = code;
            this->event = Event(event, this->code);
        }
        _setUnavailableCode(this->code);
    }
    
    

    string fpath = model->Attribute("file");
    if (fileModels.find(fpath) == fileModels.end()) {

        fileModels[fpath] = GeometricShape::readFrom3DFileVBOMode(fpath);
    }
    this->modelName = fpath;
}

void Model::run() {   
    if (mt_drawCodeColour) {
        if (this->code <= 0) {
            return;
        } 
        float colorCode = this->code / 255.0f;
        glColor3f(colorCode, colorCode, colorCode);
    }  else {
        this->colour.run();
    }
    
    
    if (this->disableCull)
        glDisable(GL_CULL_FACE);
    
    GeometricShape::drawObjectVBOMode(fileModels[this->modelName]);
    
    if (this->disableCull)
        glEnable(GL_CULL_FACE);
      
    this->event.run();
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

    const XMLAttribute * hasXML = group->FindAttribute("file");
    if (hasXML) {
        XMLDocument doc;
        try {
            XMLError read_error = doc.LoadFile(group->Attribute("file"));
        if (read_error != XML_SUCCESS) throw read_error;
        } catch (XMLError error) {
            cout << error << endl;
        }
        
        XMLElement * g;
        
        try {
            g = doc.FirstChildElement("group");
            if (g == nullptr) 
                throw std::runtime_error("Error finding first Node group in file '" + string(group->Attribute("file")) + "' !");
        } catch (const char* message) {
            cout << message << endl;
        }

        this->groups.push_back(Group(g));
    }



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
        else if (value == "text") {
            this->texts.push_back(Text(child));
        }
        else {
            throw std::runtime_error("Invalid group child value '" + std::string(child->Value()) + "'!");
        }

        child = child->NextSiblingElement();
    }

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
    for (Text t : this->texts) {
        t.run();
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

_3f _3f::cross(const _3f &other) const {
    _3f result;
    result.x = y * other.z - z * other.y;
    result.y = z * other.x - x * other.z;
    result.z = x * other.y - y * other.x;
    return result;
}

_3f& _3f::operator+=(const _3f &other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

_3f& _3f::operator-=(const _3f &other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}



void FirstPersonCamera::update(float deltaTime, bool forward, bool backward, bool left, bool right, float mouseX, float mouseY) {
    // Update pitch and yaw based on mouse input
    pitch += mouseY;
    yaw += mouseX;

    // Clamp pitch to prevent camera flipping
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Update camera direction
    updateVectors();

    // Update position based on keyboard input
    _3f forwardVec = lookAt - position;
    forwardVec.normalize();
    _3f rightVec = forwardVec.cross(up);
    rightVec.normalize();

    if (forward) position += forwardVec * movementSpeed * deltaTime;
    if (backward) position -= forwardVec * movementSpeed * deltaTime;
    if (left) position -= rightVec * movementSpeed * deltaTime;
    if (right) position += rightVec * movementSpeed * deltaTime;

    // Update lookAt based on new position
    lookAt = position + forwardVec;
}

void FirstPersonCamera::updateVectors() {
    _3f newDirection;
    newDirection.x = cos(yaw) * cos(pitch);
    newDirection.y = sin(pitch);
    newDirection.z = sin(yaw) * cos(pitch);
    lookAt = position + newDirection;
}
