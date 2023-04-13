//
// Created by user13 on 04-03-2023.
//
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <GLUT/glew.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif
#define GLUT_

#include "geometricShapes.h"
#include "engineMaterials.h"

using namespace std;

//GLuint vertices, verticeCount;

World * world;

//vector<Point> vertexB;

void changeSize(int w, int h) {

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if(h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    Point proj = world->getCamera().getProjection();

    gluPerspective(proj.x ,ratio, proj.y ,proj.z);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {

    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();

    Point position = world->getCamera().getPosition();
    Point lookAt = world->getCamera().getLookAt();
    Point up = world->getCamera().getUp();
    

    gluLookAt(position.x, position.y, position.z,
              lookAt.x, lookAt.y, lookAt.z,
              up.x, up.y, up.z);

    //gluLookAt(0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1, 0);

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    using transformatonFunc = void(*)(...);
    for (auto transf : trans->transformations) {
        transformatonFunc function = reinterpret_cast<transformatonFunc>(transf);
        
        if (function == reinterpret_cast<transformatonFunc>(&applyTranslation)) {

        }
    
    }


    // End of frame
    glutSwapBuffers();
}

int is_skeleton = 0;
void processKeys(unsigned char key, int x, int y) {
    if (key == 'x') {
        if (is_skeleton)
            glPolygonMode(GL_FRONT, GL_FILL);
        else
            glPolygonMode(GL_FRONT, GL_LINE);
        is_skeleton = !is_skeleton;
        cout << "Pressed: " << key << endl;
    }
    glutPostRedisplay();
}



// Para executar, ir para a pasta build, "make group_project", "./group_project"
int main(int argc, char ** argv) {

    cout << "aqui" << endl;
    // init glut and window
    world = new World(
        Window(800, 800),
        Camera(
            Point(5, 6, 15),
            Point(0, 0, 0),
            Point(0, 1, 0),
            Point(60, 1, 1000)
     ));
    cout << "aqui2" << endl;
    
    trans->transformations.push_back(applyTranslation(Point(0, 1, 0)));
    trans->transformations.push_back(drawModel(GeometricShape::readFrom3DFile("cone_1_2_4_3.3d")));
    trans->transformations.push_back(applyTranslation(Point(0, 3, 0)));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowPosition(100, 100);

    glutInitWindowSize(world->getWindow().getWidth(), world->getWindow().getHeight());
    glutCreateWindow("Engine");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Glew
    //glewInit();
    //glEnableClientState(GL_VERTEX_ARRAY);
    //glGenBuffers(1, &vertices);


    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    //glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    // Glut's main cycle
    glutMainLoop();


    /*
    world = new World("../../test_files/test_files_phase_2/test_2_2.xml");
    vector<string> fic = world->getFiles();
    proj = world->getCamera().getProjection();

    for (const auto &elem : world->getTransformationChain()) {
        for (const auto &elem3 : elem.transformations) {
            elem3.apply();
            cout << "sucess" << endl;
        }
    }

    c = world->getCamera();
    p = c.getPosition();
    la = c.getLookAt();
    up = c.getUp();

    for (auto elem : world->getFiles()) {
        vector<Point> tmp = GeometricShape::readFrom3DFile(elem);
        for (auto p: tmp) {
            points.push_back(p);
        }
    }
    */

    return 0;
}

