#include "XMLNode.h"
#include "XMLAttr.h"
#include "XMLTag.h"

#include <iostream>

using namespace std;

XMLTag::XMLTag(string name) {
	this->name = name;
	children = new list<XMLNode *>();
	attrs = new list<XMLAttr>();
}

string XMLTag::get_name() {
	return name;
}

void XMLTag::add_child(XMLNode *child) {
	children->push_back(child);
	child->set_parent(this);
}

list<XMLNode *>* XMLTag::get_children() {
	return children;
}

void XMLTag::add_attr(XMLAttr attr) {
	attrs->push_back(attr);
}

list<XMLAttr>* XMLTag::get_attrs() {
	return attrs;
}