#include "XMLAttr.h"
#include "XMLNode.h"
#include "XMLTag.h"

void XMLNode::set_parent(XMLTag* parent) {
	this->parent = parent;
}

NODE_TYPE XMLNode::get_type() {
	return type;
}

int XMLNode::get_depth() {
	return depth;
}

void XMLNode::set_depth(int depth) {
	this->depth = depth;
}
