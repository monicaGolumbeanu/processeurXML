#include "XMLNode.h"

XMLNode::XMLNode(NODE_TYPE type) {
    this->type = type;
}

void XMLNode::setParent(XMLTag* parent) {
    this->parent = parent;
}

XMLTag* XMLNode::getParent() {
    return parent;
}

NODE_TYPE XMLNode::getType() {
    return type;
}

int XMLNode::getDepth() {
    return depth;
}

void XMLNode::setDepth(int depth) {
    this->depth = depth;
}

bool XMLNode::getVisited() {
    return visited;
}

void XMLNode::setVisited(bool visited) {
    this->visited = visited;
}
