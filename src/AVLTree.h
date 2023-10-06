#pragma once
#include <string>
#include <queue>
#include <stack>
#include "Node.h"

using std::string;
using std::cout;
using std::endl;

class AVLTree {
	Node* root;
	Node* gp;
	Node* p;
	Node* ShiftLeft(Node* node);
	Node* ShiftRight(Node* node);
	int Height(Node* node);
	void Balance(Node* grandparent, Node* parent);
	void IncrementGrandparent(Node* grandparent, Node* parent);
	void IncrementParent(Node* parent, Node* child);
	Node* InsertHelper(Node* node, string name, string ufid);
	void RemoveHelper(Node* node, string ufid);
	void SearchNameHelper(string name);
	void SearchIDHelper(Node* node, string ufid);
	void PrintLevelCountHelper();
	void RemoveInorderHelper(Node* node, int n);
	void PrintInorderHelper(Node* node);
	void PrintPreorderHelper(Node* node);
	void PrintPostorderHelper(Node* node);

public:
	AVLTree();
	~AVLTree();
	void Insert(string name, string ufid);
	void Remove(string ufid);
	void SearchName(string name);
	void SearchID(string ufid);
	void PrintInorder();
	void PrintPreorder();
	void PrintPostorder();
	void PrintLevelCount();
	void RemoveInorder(int n);
};