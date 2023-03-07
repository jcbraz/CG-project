#ifndef GROUP_PROJECT_PARSEXML_H
#define GROUP_PROJECT_PARSEXML_H

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct XMLException : public exception {
    
};

/*
 * CAMERA SECTION
 */

struct Position {
    int x;
    int y;
    int z;
};

struct LookAt {
    int x;
    int y;
    int z;
};

struct Up {
    int x;
    int y;
    int z;
};

struct Projection {
    float fov;
    float near;
    float far;
};

class Camera {
   private:
    Position position;
    LookAt lookAt;
    Up up;
    Projection projection;

   public:
    Camera();
    Camera(const Camera& camera);
    Camera(Position position, LookAt lookAt, Up up, Projection projection);
    Camera(int position_x, int position_y, int position_z, int lookAt_x,
           int lookAt_y, int lookAt_z, int up_x, int up_y, int up_z,
           float projection_fov, float projection_near, float projection_far);
};

/*
 * WORLD SECTION
 */

class World {
   private:
    int width;
    int height;
    Camera camera;
    vector<string> files;

   public:
    World();
    World(int width, int height, vector<string> files);
    World(const Camera& camera, int width, int height, vector<string> files);
};

#endif  // GROUP_PROJECT_PARSEXML_H