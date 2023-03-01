#include <string>

#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

bool parseXML(string filepath) {
    XMLDocument xml_doc;
    char* new_filepath = new char[filepath.length() + 1];
    strcpy(new_filepath, filepath.c_str());

    XMLError read_result = xml_doc.LoadFile((const char*)new_filepath);
    if (read_result != XML_SUCCESS) return false;

    XMLNode* root = xml_doc.FirstChildElement("world");
    if (root == nullptr) return false;

    XMLElement* element = root->FirstChildElement("window");
    if (element == nullptr)
        return false;

    return true;
}

int main() {
    parseXML("file.xml");
}