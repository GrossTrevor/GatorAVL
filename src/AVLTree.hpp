#include "AVLTree.h"

using std::string;
using std::cout;
using std::endl;
using std::queue;
using std::stack;

bool firstNode = true;
bool balanceTime = false;
bool removeFound = false;
bool firstInorder = true;
bool firstPreorder = true;
bool firstPostorder = true;
bool successfulInsert = false;
bool shifted = false;

int levelCount = 0;
int removeCount = 0;

AVLTree::AVLTree() {
	root = nullptr;
}

AVLTree::~AVLTree() {
	if (root != nullptr) {
		Node* temp = root;
		stack<Node*> s;
		s.push(temp);
		while (temp != nullptr) {
			temp = s.top();
			s.pop();
			if (temp->right != nullptr)
				s.push(temp->right);
			if (temp->left != nullptr)
				s.push(temp->left);
			delete temp;
		}
	}
}

Node* AVLTree::GetRoot() {
	return root;
}

Node* AVLTree::ShiftLeft(Node* node) {
	Node* grandchild = node->right->left;
	Node* newParent = node->right;
	newParent->left = node;
	node->right = grandchild;
	if (node == root)
		root = newParent;
	node->height = 1 + std::max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);
	if (grandchild != nullptr)
		grandchild->height = 1 + std::max(grandchild->left ? grandchild->left->height : 0, grandchild->right ? grandchild->right->height : 0);
	newParent->height = 1 + std::max(newParent->left ? newParent->left->height : 0, newParent->right ? newParent->right->height : 0);
	return newParent;
}

Node* AVLTree::ShiftRight(Node* node) {
	Node* grandchild = node->left->right;
	Node* newParent = node->left;
	newParent->right = node;
	node->left = grandchild;
	if (node == root)
		root = newParent;
	node->height = 1 + std::max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);
	if (grandchild != nullptr)
		grandchild->height = 1 + std::max(grandchild->left ? grandchild->left->height : 0, grandchild->right ? grandchild->right->height : 0);
	newParent->height = 1 + std::max(newParent->left ? newParent->left->height : 0, newParent->right ? newParent->right->height : 0);
	return newParent;
}

Node* AVLTree::InsertHelper(Node* node, string name, string ufid) {
	if (node == nullptr) {
		node = new Node;
		node->name = name;
		node->ufid = ufid;
		node->left = nullptr;
		node->right = nullptr;
		successfulInsert = true;
		if (firstNode) {
			firstNode = false;
			root = node;
		}
	}
	else if (node->ufid == ufid) {
		cout << "unsuccessful" << endl;
	}
	else if (node->ufid > ufid) {
		node->left = InsertHelper(node->left, name, ufid);
	}
	else if (node->ufid < ufid) {
		node->right = InsertHelper(node->right, name, ufid);
	}
	node->height = 1 + std::max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);

	if (node->left != nullptr && node->right != nullptr && (node->left->height - node->right->height) > 1) {
		if(node->left->left != nullptr && node->left->right != nullptr && node->left->left->height > node->left->right->height)
			node = ShiftRight(node);
		else if (node->left->left != nullptr && node->left->right != nullptr && node->left->left->height < node->left->right->height) {
			node->left = ShiftLeft(node->left);
			node = ShiftRight(node);
		}
		else if (node->left->left != nullptr && node->left->right == nullptr)
			node = ShiftRight(node);
		else if (node->left != nullptr && node->left->right != nullptr) {
			node->left = ShiftLeft(node->left);
			node = ShiftRight(node);
		}
		else {
			node = ShiftRight(node);
		}
	}
	else if (node->left != nullptr && node->right == nullptr && node->left->height > 1) {
		if (node->left->left != nullptr && node->left->right != nullptr && node->left->left->height > node->left->right->height)
			node = ShiftRight(node);
		else if (node->left->left != nullptr && node->left->right != nullptr && node->left->left->height < node->left->right->height) {
			node->left = ShiftLeft(node->left);
			node = ShiftRight(node);
		}
		else if (node->left->left != nullptr && node->left->right == nullptr)
			node = ShiftRight(node);
		else if (node->left != nullptr && node->left->right != nullptr) {
			node->left = ShiftLeft(node->left);
			node = ShiftRight(node);
		}
		else {
			node = ShiftRight(node);
		}
	}

	else if (node->left != nullptr && node->right != nullptr && (node->right->height - node->left->height) > 1) {
		if (node->right->right != nullptr && node->right->left != nullptr && node->right->right->height > node->right->left->height)
			node = ShiftLeft(node);
		else if (node->right->right != nullptr && node->right->left != nullptr && node->right->right->height < node->right->left->height) {
			node->right = ShiftRight(node->right);
			node = ShiftLeft(node);
		}
		else if (node->right->right != nullptr && node->right->left == nullptr)
			node = ShiftLeft(node);
		else if (node->right != nullptr && node->right->left != nullptr) {
			node->right = ShiftRight(node->right);
			node = ShiftLeft(node);
		}
		else {
			node = ShiftLeft(node);
		}
	}
	else if (node->right != nullptr && node->left == nullptr && node->right->height > 1) {
		if (node->right->right != nullptr && node->right->left != nullptr && node->right->right->height > node->right->left->height)
			node = ShiftLeft(node);
		else if (node->right->right != nullptr && node->right->left != nullptr && node->right->right->height < node->right->left->height) {
			node->right = ShiftRight(node->right);
			node = ShiftLeft(node);
		}
		else if (node->right->right != nullptr && node->right->left == nullptr)
			node = ShiftLeft(node);
		else if (node->right != nullptr && node->right->left != nullptr) {
			node->right = ShiftRight(node->right);
			node = ShiftLeft(node);
		}
		else {
			node = ShiftLeft(node);
		}
	}
	return node;
}

void AVLTree::RemoveHelper(Node* node, string ufid, Node* p){
	if (node == nullptr) {
		if(!removeFound)
			cout << "unsuccessful" << endl;
		return;
	}
	else if (node->ufid == ufid) {
		if (node->left == nullptr && node->right == nullptr) {
			if (node != root){
				if (p->left == node)
					p->left = nullptr;
				else
					p->right = nullptr;
				}
			removeFound = true;
			delete node;
		}
		else if (node->left == nullptr) {
			if (p->left == node)
				p->left = node->right;
			else
				p->right = node->right;
			removeFound = true;
			delete node;
		}
		else if (node->right == nullptr) {
			if (p->left == node)
				p->left = node->left;
			else
				p->right = node->left;
			removeFound = true;
			delete node;
		}
		else {
			Node* min = node;
			p = node;
			while (min->left != nullptr) {
				p = min;
				min = min->left;
			}
			node->name = min->name;
			node->ufid = min->ufid;
			if (min->right != nullptr) {
				p->left = min->right;
			}
			else {
				p->left = nullptr;
			}
			removeFound = true;
			delete min;
		}
		cout << "successful" << endl;
		return;
	}
	else if (node->ufid < ufid) {
		RemoveHelper(node->right, ufid, node);
	}
	else if (node->ufid > ufid) {
		RemoveHelper(node->left, ufid, node);
	}
	else {
		cout << "unsuccessful" << endl;
		return;
	}
}

void AVLTree::SearchNameHelper(string name) {
	bool found = false;
	if (root == nullptr) {
		cout << "unsuccessful" << endl;
		return;
	}
	Node* temp = GetRoot();
	stack<Node*> s;
	s.push(temp);
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		if (temp->name == name) {
			cout << temp->ufid << endl;
			found = true;
		}
		if (temp->right != nullptr)
			s.push(temp->right);
		if (temp->left != nullptr)
			s.push(temp->left);
	}
	if (!found)
		cout << "unsuccessful" << endl;
}

void AVLTree::SearchIDHelper(Node* node, string ufid) {
	if (node == nullptr) {
		cout << "unsuccessful" << endl;
		return;
	}
	if (node->ufid == ufid) {
		cout << node->name << endl;
		return;
	}
	else if (node->ufid < ufid) {
		SearchIDHelper(node->right, ufid);
	}
	else if (node->ufid > ufid) {
		SearchIDHelper(node->left, ufid);
	}
}

void AVLTree::PrintInorderHelper(Node* node) {
	if (node == nullptr)
		return;
	PrintInorderHelper(node->left);
	if (firstInorder) {
		cout << node->name;
		firstInorder = false;
	}
	else {
		cout << ", " << node->name;
	}
	PrintInorderHelper(node->right);

}

void AVLTree::PrintPreorderHelper(Node* node) {
	if (node == nullptr)
		return;
	if (firstPreorder) {
		cout << node->name;
		firstPreorder = false;
	}
	else
		cout << ", " << node->name;
	PrintPreorderHelper(node->left);
	PrintPreorderHelper(node->right);
}

void AVLTree::PrintPostorderHelper(Node* node) {
	if (node == nullptr)
		return;
	PrintPostorderHelper(node->left);
	PrintPostorderHelper(node->right);
	if (firstPostorder) {
		cout << node->name;
		firstPostorder = false;
	}
	else
		cout << ", " << node->name;
}

void AVLTree::PrintLevelCountHelper() {
	if (root == nullptr) {
		cout << "0" << endl;
		return;
	}
	queue<Node*> q;
	int count = 0;
	int countChild = 0;
	int prevCountChild = 1;
	int level = 0;
	q.push(root);
	while (q.empty() == false) {
		Node* node = q.front();

		if (node->left != nullptr) {
			q.push(node->left);
			countChild++;
			count++;
		}
		else if (node->left == nullptr)
			count++;

		if (node->right != nullptr) {
			q.push(node->right);
			countChild++;
			count++;
		}
		else if (node->right == nullptr)
			count++;

		if ((prevCountChild * 2) == count) {
			level++;
			prevCountChild = countChild;
			count = 0;
			countChild = 0;
		}
		q.pop();
	}
	cout << level << endl;
}

void AVLTree::RemoveInorderHelper(Node* node, int n) {
	if (node == nullptr)
		return;
	RemoveInorderHelper(node->left, n);
	if (n == 0) {
		Remove(node->ufid);
		return;
	}
	RemoveInorderHelper(node->right, n - 1);
}

void AVLTree::Insert(string name, string ufid) {
	InsertHelper(GetRoot(), name, ufid);
	if (successfulInsert) {
		cout << "successful" << endl;
		successfulInsert = false;
	}
}

void AVLTree::Remove(string ufid) {
	RemoveHelper(GetRoot(), ufid, nullptr);
}

void AVLTree::SearchName(string name) {
	SearchNameHelper(name);
}

void AVLTree::SearchID(string ufid) {
	SearchIDHelper(GetRoot(), ufid);
}

void AVLTree::PrintInorder() {
	if (GetRoot() == nullptr) {
		cout << "unsuccessful" << endl;
		return;
	}
	PrintInorderHelper(GetRoot());
	firstInorder = true;
	cout << endl;
}

void AVLTree::PrintPreorder() {
	if (GetRoot() == nullptr) {
		cout << "unsuccessful" << endl;
		return;
	}
	PrintPreorderHelper(GetRoot());
	firstPreorder = true;
	cout << endl;
}

void AVLTree::PrintPostorder() {
	if (GetRoot() == nullptr) {
		cout << "unsuccessful" << endl;
		return;
	}
	PrintPostorderHelper(GetRoot());
	firstPostorder = true;
	cout << endl;
}

void AVLTree::PrintLevelCount() {
	PrintLevelCountHelper();
}

void AVLTree::RemoveInorder(int n) {
	RemoveInorderHelper(GetRoot(), n);
}