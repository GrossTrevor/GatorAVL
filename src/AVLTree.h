#pragma once
#include <string>
#include <queue>
#include <stack>
#include "Node.h"

using std::string;
using std::cout;
using std::endl;

//AVL Tree class
class AVLTree {
	Node* root;
	Node* GetRoot();
	Node* ShiftLeft(Node* node);
	Node* ShiftRight(Node* node);
	Node* InsertHelper(Node* node, string name, string ufid);
	void RemoveHelper(Node* node, string ufid, Node* parent);
	void SearchNameHelper(string name);
	void SearchIDHelper(Node* node, string ufid);
	void PrintInorderHelper(Node* node);
	void PrintPreorderHelper(Node* node);
	void PrintPostorderHelper(Node* node);
	void PrintLevelCountHelper();
	void RemoveInorderHelper(Node* node, int n);

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