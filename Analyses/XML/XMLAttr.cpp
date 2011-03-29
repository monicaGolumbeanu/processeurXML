#include <string>
#include "XMLAttr.h"

using namespace std;

XMLAttr::XMLAttr(string name, string value) {
    this->name = name;
    this->value = value;
}

string XMLAttr::getName() {
    return name;
}

string XMLAttr::getValue() {
    return value;
}
