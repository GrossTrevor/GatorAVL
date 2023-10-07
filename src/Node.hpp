#include "Node.h"

//Construct an empty node
Node::Node() {
	this->name = "";
	this->ufid = "";
	this->left = nullptr;
	this->right = nullptr;
	this->height = 0;
}