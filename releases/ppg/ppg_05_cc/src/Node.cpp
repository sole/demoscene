#include "Node.h"

Node::Node() {
	this->updated=false;
}

Node::~Node() {
}

void Node::deInit() {
}

bool Node::isUpdated() {
	return this->updated;
}

void Node::perFrame(float time) {
}