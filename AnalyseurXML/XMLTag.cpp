#include "XMLVisitor.h"
#include "XMLNode.h"
#include "XMLAttr.h"
#include "XMLTag.h"

#include <iostream>
#include <string>
#include <list>

using namespace std;

XMLTag::XMLTag(string name) {
	this->name = name;
	children = new list<XMLNode *>();
	attrs = new list<XMLAttr>();
	type = NODE_XMLTAG;
	depth = 0;
}

string XMLTag::get_name() {
	return name;
}

void XMLTag::add_child(XMLNode *child) {
	children->push_back(child);
	child->set_parent(this);
	child->set_depth(depth+1);
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

/*void XMLTag::accept(XMLVisitor* v) {
	v->visitXMLTag(this);
}*/
