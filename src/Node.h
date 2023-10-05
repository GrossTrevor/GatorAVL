#pragma once
#include <string>
#include <AVLTree.h>

using std::string;

struct Node {
	string name;
	string ufid;
	Node* left;
	Node* right;
	Node();
};