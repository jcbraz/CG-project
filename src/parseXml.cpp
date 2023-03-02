#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "tinyxml2/tinyxml2.cpp"

using namespace std;
using namespace tinyxml2;

bool parseXML(string filepath) {
    XMLDocument xml_doc;

    XMLError read_result = xml_doc.LoadFile(filepath.c_str());
    if (read_result != XML_SUCCESS) {
        cout << "Error loading XML file: " << read_result << endl;
        return false;
    }

    XMLNode* root = xml_doc.FirstChildElement("world");
    if (root == nullptr) {
        cout << "Error finding 'world' node" << endl;
        return false;
    }

    XMLElement* element = root->FirstChildElement("window");
    if (element == nullptr) {
        cout << "Error finding 'window' node" << endl;
        return false;
    }

    return true;
}

int main() {
    bool result = parseXML("./config/config.xml");
    cout << result << endl;
}
