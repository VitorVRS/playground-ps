#include "node.h"
#include <iostream>

Node::Node() {
	this->count = 0;
}

void Node::addChildren(Node * children) {
	this->childrens.push_back(children);
	this->count++;
}

void Node::setValue(std::string value) {
	this->value = value;
}

Node * Node::getParent() {
	return this->parent;
}

void Node::setParent(Node * parent) {
	this->parent = parent;
}

unsigned int Node::getCount() {
	return this->count;
}

void Node::doPrint(int level) {

	std::cout << std::string(level, ' ') << "LEVEL: " << level << " - VALUE: " << this->value <<  "\n";

	for (unsigned int i = 0; i < this->childrens.size(); i++) {
		this->childrens[i]->doPrint(level+1);
	}
}

void Node::doPrint() {
	this->doPrint(0);
}
