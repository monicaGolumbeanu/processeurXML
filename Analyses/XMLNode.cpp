#include "XMLNode.h"

XMLNode::XMLNode(NODE_TYPE type) {
	this->type = type;
}

void XMLNode::set_parent(XMLTag* parent) {
	this->parent = parent;
}

XMLTag* XMLNode::get_parent() {
	return this->parent;
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

bool XMLNode::get_visited() {
	return visited;
}

void XMLNode::set_visited(bool visited) {
	this->visited = visited;
}
