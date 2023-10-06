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
	gp = nullptr;
	p = nullptr;
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

Node* AVLTree::ShiftLeft(Node* node) {
	Node* grandchild = node->right->left;
	Node* newParent = node->right;
	newParent->left = node;
	node->right = grandchild;
	cout << "root name: " << root->name << endl;
	if (node == root)
		root = newParent;
	cout << "new root name: " << root->name << endl;
	cout << "shifted left" << endl;
	node->height = 1 + std::max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);
	if (grandchild != nullptr)
		grandchild->height = 1 + std::max(grandchild->left ? grandchild->left->height : 0, grandchild->right ? grandchild->right->height : 0);
	newParent->height = 1 + std::max(newParent->left ? newParent->left->height : 0, newParent->right ? newParent->right->height : 0);
	cout << "I MADE IT HERE" << endl;
	return newParent;
}

Node* AVLTree::ShiftRight(Node* node) {
	Node* grandchild = node->left->right;
	Node* newParent = node->left;
	newParent->right = node;
	node->left = grandchild;
	cout << "root name: " << root->name << endl;
	if (node == root)
		root = newParent;
	cout << "new root name: " << root->name << endl;
	cout << "shifted right" << endl;
	node->height = 1 + std::max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);
	if (grandchild != nullptr)
		grandchild->height = 1 + std::max(grandchild->left ? grandchild->left->height : 0, grandchild->right ? grandchild->right->height : 0);
	newParent->height = 1 + std::max(newParent->left ? newParent->left->height : 0, newParent->right ? newParent->right->height : 0);
	cout << "I MADE IT HERE" << endl;
	return newParent;
}

//int AVLTree::Height(Node* node) {
//	if (node == nullptr) {
//		return 0;
//	}
//	queue<Node*> q;
//	int count = 0;
//	int countChild = 0;
//	int prevCountChild = 1;
//	int level = 0;
//	cout << "Node name: " << node->name << endl;
//	q.push(node);
//	while (q.empty() == false) {
//		Node* temp = q.front();
//
//		if (temp->left != nullptr) {
//			q.push(temp->left);
//			cout << "temp->left: " << temp->left->name << endl;
//			countChild++;
//			count++;
//		}
//		else if (temp->left == nullptr)
//			count++;
//
//		if (temp->right != nullptr) {
//			q.push(temp->right);
//			cout << "temp->right: " << temp->right->name << endl;
//			countChild++;
//			count++;
//		}
//		else if (temp->right == nullptr)
//			count++;
//
//		if ((prevCountChild * 2) == count) {
//			level++;
//			prevCountChild = countChild;
//			count = 0;
//			countChild = 0;
//		}
//		q.pop();
//	}
//	return level;
//}

//void AVLTree::Balance(Node* grandparent, Node* parent) {
//	cout << "balancing" << endl;
//	if (grandparent == nullptr || parent == nullptr) {
//		cout << "not balancing" << endl;
//		return;
//	}
//
//	cout << grandparent->name << endl;
//	cout << parent->name << endl;
//
//	cout << "gp right name: " << grandparent->right->name << endl;
//	cout << "p right name: " << parent->right->name << endl;
//
//	int parentBalance = Height(grandparent->left) - Height(grandparent->right);
//	int childBalance = Height(parent->left) - Height(parent->right);
//
//	cout << Height(grandparent->left) << endl;
//	cout << Height(grandparent->right) << endl;
//	cout << Height(parent->left) << endl;
//	cout << Height(parent->right) << endl;
//
//	cout << parentBalance << endl;
//	cout << childBalance << endl;
//
//	if (parentBalance == 2 && childBalance == 1)
//		ShiftRight(grandparent);
//
//	if (parentBalance == 2 && childBalance == -1) {
//		ShiftLeft(parent);
//		ShiftRight(grandparent);
//	}
//
//	if (parentBalance == -2 && childBalance == -1)
//		ShiftLeft(grandparent);
//
//	if (parentBalance == -2 && childBalance == 1) {
//		ShiftRight(parent);
//		ShiftLeft(grandparent);
//	}
//}

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

void AVLTree::Insert(string name, string ufid) {
	InsertHelper(root, name, ufid);
	if (successfulInsert) {
		cout << "successful" << endl;
		successfulInsert = false;
	}
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
	firstInorder = true;
	cout << endl;
}

void AVLTree::PrintPreorder() {
	PrintPreorderHelper(root);
	firstPreorder = true;
	cout << endl;
}

void AVLTree::PrintPostorder() {
	PrintPostorderHelper(root);
	firstPostorder = true;
	cout << endl;
}

void AVLTree::PrintLevelCount() {
	PrintLevelCountHelper();
}

void AVLTree::RemoveInorder(int n) {
	RemoveInorderHelper(root, n);
}