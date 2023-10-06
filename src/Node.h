#pragma once
#include <string>

using std::string;

struct Node {
	string name;
	string ufid;
	Node* left;
	Node* right;
	int height;
	Node();
};