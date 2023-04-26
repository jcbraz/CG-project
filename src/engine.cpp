//
// Created by user13 on 04-03-2023.
//
#include <math.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <IL/il.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#define GLUT_

// #include "engineMaterials.h"
// #include "parseXML.h"
#include "geometricShapes.h"
#include "materials.h"

using namespace std;

int startX, startY, tracking = 0;
float _alpha = 0, _beta = 35, r = 10;
int polygonMode = GL_FILL;

World * world;
Window * window;
Camera * camera;
Group * group;

vector<std::tuple<GLuint, int, int>> test;

int timebase = 0;
float frames = 0;

void displayFrameRate() {
    char title[50];
    frames++;
    double time = glutGet(GLUT_ELAPSED_TIME);

    if (time - timebase > 1000) {
        double fps = frames * 1000.0 / (time - timebase);
        timebase = time;
        frames = 0;
        sprintf(title, "Engine | %lf FPS", fps);
        glutSetWindowTitle(title);
    }
}

// vector<Point> vertexB;

void changeSize(int w, int h) {
    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0) h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective


    _3f proj = camera->getProjection();
    gluPerspective(proj.x, ratio, proj.y, proj.z);

    //gluPerspective(60, ratio, 1, 1000);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    _3f position = camera->getPosition();
    _3f lookAt = camera->getLookAt();
    _3f up = camera->getUp();

    gluLookAt(position.x, position.y, position.z, lookAt.x, lookAt.y, lookAt.z,
              up.x, up.y, up.z);

    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-1000.0f, 0.0f, 0.0f);
    glVertex3f(1000.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -1000.0f, 0.0f);
    glVertex3f(0.0f, 1000.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -1000.0f);
    glVertex3f(0.0f, 0.0f, 1000.0f);
    glEnd();

    group->run();
    //glColor3f(1.0f, 1.0f, 1.0f);
    //GeometricShape::drawObjectVBOMode(test);

    displayFrameRate();

    // End of frame
    glutSwapBuffers();
}

bool is_cull = true;
void processKeys(unsigned char key, int x, int y) {
    switch (key) {
        case 'l':
            polygonMode = GL_LINE;
            break;
        case 'p':
            polygonMode = GL_POINT;
            break;
        case 'f':
            polygonMode = GL_FILL;
            break;
        case 'c':
            if (is_cull)
                glDisable(GL_CULL_FACE);
            else
                glEnable(GL_CULL_FACE);
            is_cull = !is_cull;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void processMouseButtons(int button, int state, int xx, int yy) {
    if (state == GLUT_DOWN) {
        startX = xx;
        startY = yy;
        if (button == GLUT_LEFT_BUTTON)
            tracking = 1;
        else if (button == GLUT_RIGHT_BUTTON)
            tracking = 2;
        else {
            tracking = 0;
            picking(xx, yy, camera, group);

            glutPostRedisplay();
        }
    } else if (state == GLUT_UP) {
        if (tracking == 1) {
            _alpha += (xx - startX);
            _beta += (yy - startY);
        } else if (tracking == 2) {
            r -= yy - startY;
            if (r < 3) r = 3.0;
        }
        tracking = 0;
    }
}

void processMouseMotion(int xx, int yy) {
    int deltaX, deltaY;
    int _alphaAux, _betaAux;
    int rAux;

    if (!tracking) return;

    deltaX = xx - startX;
    deltaY = yy - startY;

    if (tracking == 1) {
        _alphaAux = _alpha + deltaX;
        _betaAux = _beta + deltaY;

        if (_betaAux > 85.0)
            _betaAux = 85.0;
        else if (_betaAux < -85.0)
            _betaAux = -85.0;

        rAux = r;
    } else if (tracking == 2) {
        _alphaAux = _alpha;
        _betaAux = _beta;
        rAux = r - deltaY;
        if (rAux < 3) rAux = 3;
    }
    float camX =
        rAux * sin(_alphaAux * 3.14 / 180.0) * cos(_betaAux * 3.14 / 180.0);
    float camZ =
        rAux * cos(_alphaAux * 3.14 / 180.0) * cos(_betaAux * 3.14 / 180.0);
    float camY = rAux * sin(_betaAux * 3.14 / 180.0);
    camera->setPosition(_3f(camX, camY, camZ));

    glutPostRedisplay();
}

// Para executar, ir para a pasta build, "make group_project", "./group_project"
int main(int argc, char** argv) {


    string path = "../../test_files/solar_system/solar_system.xml";
    //string path = "../../test_files/test_files_phase_2/test_2_solar.xml";

    srand(time(nullptr));

    world = new World(path);
    window = new Window(world->getWindow());
    camera = new Camera(world->getCamera());

    // init glut and window

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);

    glutInitWindowSize(window->getWidth(), window->getHeight());
   //glutInitWindowSize(1000, 1000);
    glutCreateWindow("Engine");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Glew --> activate if not in mac
    glewInit();
    glEnableClientState(GL_VERTEX_ARRAY);

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    // glutSpecialFunc(processSpecialKeys);

    // Callback registration for mouse processing
    glutMouseFunc(processMouseButtons);
    glutMotionFunc(processMouseMotion);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    ilInit();
    // frames
    timebase = glutGet(GLUT_ELAPSED_TIME);

    world->evaluateGroup(path);
    group = new Group(world->getGroup());


    /*
    TESTE
    
    //Sphere s = Sphere(1, 35, 35, 25, "boas");
    //test = GeometricShape::convertToVBO(s.getPoints());
    */

    // Glut's main cycle
    glutMainLoop();

    return 0;
}
