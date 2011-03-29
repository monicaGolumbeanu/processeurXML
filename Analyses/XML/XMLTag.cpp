#include <string>
#include <vector>
#include "XMLVisitor.h"
#include "XMLNode.h"
#include "XMLAttr.h"
#include "XMLTag.h"

using namespace std;

XMLTag::XMLTag(string name, string ns) : XMLNode(NODE_XMLTAG) {
    this->name = name;
    this->ns = ns;
    children = new vector<XMLNode *> ();
    attrs = new vector<XMLAttr*> ();
    type = NODE_XMLTAG;
    depth = 0;
}

string XMLTag::getName() {
    return name;
}

string XMLTag::getNamespace() {
    return ns;
}

void XMLTag::addChild(XMLNode *child) {
    children->push_back(child);
    child->setParent(this);
    child->setDepth(depth + 1);
}

vector<XMLNode *>* XMLTag::getChildren() {
    return children;
}

bool XMLTag::hasChildren() {
	return (children->size() > 0);
}

void XMLTag::addAttr(XMLAttr* attr) {
    attrs->push_back(attr);
}

vector<XMLAttr*>* XMLTag::getAttrs() {
    return attrs;
}

bool XMLTag::accept(XMLVisitor* v) {
    return v->visitXMLTag(this);
}
