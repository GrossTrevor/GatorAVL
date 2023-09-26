#pragma once
#include <string>
#include <queue>
#include <stack>
#include <Node.h>

using std::string;
using std::cout;
using std::endl;

class AVLTree {
private:
	Node* InsertHelper(Node* node, string name, string ufid);

public:
	Node* root;
	AVLTree();
	void Balance();
	void ShiftLeft(Node* node);
	void ShiftRight(Node* node);
	void Insert(string name, string ufid);
	void Remove(string ufid);
	void SearchName(string name);
	void SearchID(string ufid);
	void PrintInorder(Node* node);
	void PrintPreorder(Node* node);
	void PrintPostorder(Node* node);
	void PrintLevelCount();
	void RemoveInorder(Node* node, int n);
};