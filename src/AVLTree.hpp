#include "AVLTree.h"

using std::string;
using std::cout;
using std::endl;
using std::queue;
using std::stack;

bool firstNode = true;
bool removeFound = false;
bool firstInorder = true;
bool firstPreorder = true;
bool firstPostorder = true;

int levelCount = 0;
int removeCount = 0;

Node* AVLTree::ShiftLeft(Node* node) {
	Node* grandchild = node->right->left;
	Node* newParent = node->right;
	newParent->left = node;
	node->right = grandchild;
	return newParent;
}

Node* AVLTree::ShiftRight(Node* node) {
	Node* grandchild = node->left->right;
	Node* newParent = node->left;
	newParent->right = node;
	node->left = grandchild;
	return newParent;
}

int AVLTree::Height(Node* node) {
	if (node == nullptr) {
		return 0;
	}
	queue<Node*> q;
	int count = 0;
	int countChild = 0;
	int prevCountChild = 1;
	int level = 0;
	q.push(node);
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
	return level;
}

void AVLTree::Balance(Node* grandparent, Node* parent) {
	if (grandparent == nullptr || parent == nullptr)
		return;

	int parentBalance = Height(grandparent->left) - Height(grandparent->right);
	int childBalance = Height(parent->left) - Height(parent->right);

	if (parentBalance == 2 && childBalance == 1)
		grandparent = ShiftRight(grandparent);

	if (parentBalance == 2 && childBalance == -1) {
		parent = ShiftLeft(parent);
		grandparent = ShiftRight(grandparent);
	}

	if (parentBalance == -2 && childBalance == -1)
		grandparent = ShiftLeft(grandparent);

	if (parentBalance == -2 && childBalance == 1) {
		parent = ShiftRight(parent);
		grandparent = ShiftLeft(grandparent);
	}
}

Node* AVLTree::InsertHelper(Node* node, string name, string ufid) {
	if (node == nullptr) {
		node = new Node;
		node->name = name;
		node->ufid = ufid;
		node->left = nullptr;
		node->right = nullptr;
		if (firstNode) {
			firstNode = false;
			root = node;
		}
	}
	else if (node->ufid == ufid) {
		cout << "unsuccessful" << endl;
	}
	else if (node->ufid > ufid) {
		gp = p;
		p = node;
		node->left = InsertHelper(node->left, name, ufid);
	}
	else if (node->ufid < ufid) {
		gp = p;
		p = node;
		node->right = InsertHelper(node->right, name, ufid);
	}
	Balance(gp, p);
	gp = nullptr;
	p = nullptr;
	cout << "successful" << endl;
	return node;
}

void AVLTree::RemoveHelper(Node* node, string ufid){
	if (node == nullptr) {
		if(!removeFound)
			cout << "unsuccessful" << endl;
		return;
	}
	if (node->ufid == ufid) {
		if (node->left == nullptr && node->right == nullptr) {
			if (p->left == node)
				p->left = nullptr;
			else
				p->right = nullptr;
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
			Node* min = node->right;
			p = node->right;
			while (min->left != nullptr) {
				p = min;
				min = min->left;
			}
			node->name = min->name;
			node->ufid = min->ufid;
			if (min->right != nullptr) {
				p->left = min->right;
			}
			removeFound = true;
			delete min;
		}
		cout << "successful" << endl;
		return;
	}
	else if (node->ufid < ufid) {
		p = node;
		RemoveHelper(node->right, ufid);
	}
	else if (node->ufid > ufid) {
		p = node;
		RemoveHelper(node->left, ufid);
	}
	p = nullptr;
}

void AVLTree::SearchNameHelper(string name) {
	bool found = false;
	if (root == nullptr) {
		cout << "unsuccessful" << endl;
		return;
	}
	Node* temp = root;
	stack<Node*> s;
	s.push(temp);
	while (temp != nullptr) {
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
	delete temp;
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
		cout << "successful" << endl;
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

AVLTree::AVLTree() {
	root = nullptr;
	gp = nullptr;
	p = nullptr;
}

AVLTree::~AVLTree() {
	if (root != nullptr){
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

void AVLTree::Insert(string name, string ufid) {
	InsertHelper(root, name, ufid);
}

void AVLTree::Remove(string ufid) {
	RemoveHelper(root, ufid);
}

void AVLTree::SearchName(string name) {
	SearchNameHelper(name);
}

void AVLTree::SearchID(string ufid) {
	SearchIDHelper(root, ufid);
}

void AVLTree::PrintInorder() {
	PrintInorderHelper(root);
}

void AVLTree::PrintPreorder() {
	PrintPostorderHelper(root);
}

void AVLTree::PrintPostorder() {
	PrintPostorderHelper(root);
}

void AVLTree::PrintLevelCount() {
	PrintLevelCountHelper();
}

void AVLTree::RemoveInorder(int n) {
	RemoveInorderHelper(root, n);
}