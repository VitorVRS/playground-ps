#include "node.h"
#include <iostream>
#include <utility>

Node::Node() {
	this->count = 0;
}

void Node::addChildren(Node * children) {
	this->childrens.push_back(children);
	this->count++;
}

void Node::setValue(std::string value) {
	this->value = std::move(value);
}

void Node::setParent(Node * parent) {
	this->parent = parent;
}

void Node::doPrint(unsigned int level) {

	std::cout << std::string(level, ' ') << "LEVEL: " << level << " - VALUE: " << this->value <<  "\n";

	for (auto &children : this->childrens) {
		children->doPrint(level+1);
	}
}

void Node::doPrint() {
	this->doPrint(0);
}
