#include <AVLTree.h>

using std::string;

Node* AVLTree::InsertHelper(Node* node, string name, string ufid) {
	if (node == nullptr) {
		node = new Node;
		node->name = name;
		node->ufid = ufid;
		node->left = nullptr;
		node->right = nullptr;
		node->depth = 0;
	}
	else if (name < node->ufid) {
		node->SetLeft(InsertHelper(node->left, name, ufid));
	}
	else if (name > node->ufid) {
		node->SetRight(InsertHelper(node->right, name, ufid));
	}
	return node;
}

AVLTree::AVLTree() {
	this->root = nullptr;
}

void AVLTree::Balance() {

}

void AVLTree::ShiftLeft(Node* node) {

}

void AVLTree::ShiftRight(Node* node) {

}

void AVLTree::Insert(string name, string ufid) {
	this->root = InsertHelper(this->root, name, ufid);
}

void AVLTree::SetLeft(Node* node) {
	this->left = node;
}

void AVLTree::SetRight(Node* node) {
	this->right = node;
}

void AVLTree::Remove(string ufid) {

}

void AVLTree::SearchName(string name) {

}

void AVLTree::SearchID(string ufid) {

}

void AVLTree::PrintInorder(Node* root) {

}

void AVLTree::PrintPreorder(Node* root) {

}

void AVLTree::PrintPostorder(Node* root) {

}

void AVLTree::PrintLevelCount(Node* root) {

}

void AVLTree::RemoveInorder(int n) {

}