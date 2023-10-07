#pragma once
#include <string>

using std::string;

//Contains the data for each node in the tree
struct Node {
	string name;
	string ufid;
	Node* left;
	Node* right;
	int height;
	Node();
};