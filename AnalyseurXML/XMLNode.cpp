#include "XMLAttr.h"
#include "XMLNode.h"
#include "XMLTag.h"

void XMLNode::set_parent(XMLTag* parent) {
	this->parent = parent;
}
