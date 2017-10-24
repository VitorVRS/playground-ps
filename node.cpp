#include "node.h"

void Node::addChildren(Node children) {
	this->childrens.push_back(children);
}

void Node::setValue(int value) {
	this->value = value;
}

Node * Node::getParent() {
	return this->parent;
}

void Node::setParent(Node * parent) {
	this->parent = parent;
}
