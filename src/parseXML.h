#ifndef GROUP_PROJECT_PARSEXML_H
#define GROUP_PROJECT_PARSEXML_H

#include <tinyxml2.h>

#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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
    Position getPosition() { return position; }
    LookAt getLookAt() { return lookAt; }
    Up getUp() { return up; }
    Projection getProjection() { return projection; }
};

/**
 * TRANSFORMATION SECTION
 */

class Action {
   public:
    virtual ~Action() = default;
    virtual void apply() const = 0;
};

class Translation : public Action {
   public:
    Translation(float x, float y, float z)
        : coordinate_x(x), coordinate_y(y), coordinate_z(z) {}

    void apply() const override {
        // apply translation
    }

   private:
    float coordinate_x, coordinate_y, coordinate_z;
};

class Rotation : public Action {
   public:
    Rotation(float angle, float x, float y, float z)
        : angle(angle), coordinate_x(x), coordinate_y(y), coordinate_z(z) {}

    void apply() const override {
        // apply rotation
    }

   private:
    float angle, coordinate_x, coordinate_y, coordinate_z;
};

class Scale : public Action {
   public:
    Scale(float x, float y, float z)
        : coordinate_x(x), coordinate_y(y), coordinate_z(z) {}

    void apply() const override {
        // apply scaling
    }

   private:
    float coordinate_x, coordinate_y, coordinate_z;
};

class Transformation {
   private:
    std::vector<std::unique_ptr<Action>> action_list;

   public:
    Transformation() = default;

    void addTranslation(float x, float y, float z) {
        action_list.emplace_back(new Translation(x, y, z));
    }

    void addRotation(float angle, float x, float y, float z) {
        action_list.emplace_back(new Rotation(angle, x, y, z));
    }

    void addScale(float x, float y, float z) {
        action_list.emplace_back(new Scale(x, y, z));
    }

    Transformation handleTransformation(XMLElement* element);

    void apply() const {
        for (const auto& transform : action_list) {
            transform->apply();
        }
    }
};

struct TransformationsPerFile {
    vector<string> files;
    Transformation transformations;
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
    map<int, TransformationsPerFile> transformation_chain;

   public:
    World();
    World(int width, int height, vector<string> files);
    World(const Camera& camera, int width, int height, vector<string> files);
    World(const string& filepath);
    vector<string> getFiles() { return files; };
    int getWidth() { return width; };
    int getHeight() { return height; };
    Camera getCamera() { return camera; }
    map<int, TransformationsPerFile> getTransformationChain() {
        return transformation_chain;
    }
    vector<string> handleFiles(XMLElement* element);
    void handleChainedTransformations(Transformation transformation,
                                      vector<string> files);
    map<int, TransformationsPerFile> getTransformationChain();
};

#endif  // GROUP_PROJECT_PARSEXML_H