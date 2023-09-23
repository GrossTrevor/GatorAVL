#pragma once
#include <string>
#include <Node.h>

using std::string;

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
	void SetLeft(Node* node);
	void SetRight(Node* node);
	void Remove(string ufid);
	void SearchName(string name);
	void SearchID(string ufid);
	void PrintInorder(Node* root);
	void PrintPreorder(Node* root);
	void PrintPostorder(Node* root);
	void PrintLevelCount(Node* root);
	void RemoveInorder(int n);
};