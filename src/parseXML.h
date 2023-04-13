#include <vector>
#include <iostream>
#include <string>
#include <tinyxml2.h>
#include "engineMaterials.h"
#include "geometricShapes.h"

using namespace std;
using namespace tinyxml2;

World* parseWorld(const string& filepath);
void parseGroup(XMLElement* group);