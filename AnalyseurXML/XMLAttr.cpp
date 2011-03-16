#include "XMLAttr.h"

using namespace std;

XMLAttr::XMLAttr(string name, string value) {
	this->name = name;
	this->value = value;
}

string XMLAttr::get_name() {
    return name;
}

string XMLAttr::get_value() {
    return value;
}
