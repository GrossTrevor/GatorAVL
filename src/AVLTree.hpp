#include <AVLTree.h>

using std::string;
using std::cout;
using std::endl;
using std::queue;
using std::stack;

bool firstInorder = true;
bool firstPreorder = true;
bool firstPostorder = true;
int levelCount = 0;
int removeCount = 0;

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
		node->left = InsertHelper(node->left, name, ufid);
	}
	else if (name > node->ufid) {
		node->right = InsertHelper(node->right, name, ufid);
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
	bool found = false;
	Node* temp = root;
	while (temp != nullptr) {
		if (temp == ufid) {
			found = true;
			break;
		}
		else if (temp < ufid)
			temp = temp->right;
		else if (temp > ufid)
			temp = temp->left;
	}
	if (found)
		cout << "Unsuccessful" << endl;
	delete temp;
	if (!found) {
		this->root = InsertHelper(this->root, name, ufid);
		cout << "Successful" << endl;
	}
}

void AVLTree::Remove(string ufid) {
	Node* temp = root;
	Node* parent = nullptr;
	while (temp != nullptr) {
		if (temp->ufid == ufid) {
			if (temp->left == nullptr && temp->right == nullptr) {
				if (parent->left == temp)
					parent->left = nullptr;
				else
					parent->right = nullptr;
				delete temp;
			}
			else if (temp->left == nullptr) {
				if (parent->left == temp)
					parent->left = temp->right;
				else
					parent->right = temp->right;
				delete temp;
			}
			else if (temp->right == nullptr) {
				if (parent->left == temp)
					parent->left = temp->left;
				else
					parent->right = temp->left;
				delete temp;
			}
			else {
				Node* min = temp->right;
				parent = temp->right;
				while (min->left != nullptr) {
					parent = min;
					min = min->left;
				}
				temp->name = min->name;
				temp->ufid = min->ufid;
				if (min->right != nullptr) {
					parent->left = min->right;
				}
				delete min;
			}
			cout << "Successful" << endl;
			break;
		}
		else if (temp->ufid < ufid) {
			parent = temp;
			temp = temp->right;
		}
		else if (temp->ufid > ufid) {
			parent = temp;
			temp = temp->left;
		}
	}
	if (temp == nullptr) {
		cout << "Unsuccessful" << endl;
	}
	delete parent;
	delete temp;
}

void AVLTree::SearchName(string name) {
	bool found = false;
	if (root == nullptr)
		cout << "Unsuccessful" << endl;
	Node* temp = root;
	stack<Node*> s;
	s.push(temp);
	else {
		while (temp != nullptr) {
			temp = s.top();
			s.pop();
			if (temp->name == name) {
				cout << temp->ufid << endl;
				found = true;
			}
			if(temp->right != nullptr)
				s.push(temp->right);
			if(temp->left != nullptr)
				s.push(temp->left);
		}
	}
	delete temp;
	if(!found)
		cout << "Unsuccessful" << endl;
}

void AVLTree::SearchID(string ufid) {
	bool found = false;
	if (root == nullptr)
		cout << "Unsuccessful" << endl;
	Node* temp = root;
	else {
		while (temp != nullptr) {
			if (temp == ufid) {
				cout << temp->name << endl;
				found = true;
				break;
			}
			else if (temp < ufid)
				temp = temp->right;
			else if (temp > ufid)
				temp = temp->left;
		}
		if(!found)
			cout << "Unsuccessful" << endl;
	}
	delete temp;
}

void AVLTree::PrintInorder(Node* node) {
	if(node == nullptr)
		return;
	PrintInorder(node->left);
	if (firstInorder) {
		cout << node->name;
		firstInorder = false;
	}
	else {
		cout << ", " << node->name;
	}
	PrintInorder(node->right);
}

void AVLTree::PrintPreorder(Node* node) {
	if(node == nullptr)
		return;
	if(firstPreorder) {
		cout << node->name;
		firstPreorder = false;
	}
	else
		cout << ", " << node->name;
	PrintPreorder(node->left);
	PrintPreorder(node->right);
}

void AVLTree::PrintPostorder(Node* node) {
	if(node == nullptr)
		return;
	PrintPostorder(node->left);
	PrintPostorder(node->right);
	if(firstPostorder) {
		cout << node->name;
		firstPostorder = false;
	}
	else
		cout << ", " << node->name;
}

void AVLTree::PrintLevelCount() {
	if (root == nullptr) {
		cout << "Number of levels in tree: 0" << endl;
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

		if (node->getLeft() != nullptr) {
			q.push(node->getLeft());
			countChild++;
			count++;
		}
		else if (node->getLeft() == nullptr)
			count++;

		if (node->getRight() != nullptr) {
			q.push(node->getRight());
			countChild++;
			count++;
		}
		else if (node->getRight() == nullptr)
			count++;

		if ((prevCountChild * 2) == count) {
			level++;
			prevCountChild = countChild;
			count = 0;
			countChild = 0;
		}
		q.pop();
	}
	cout << "Number of levels in tree: " << level << endl;
}

void AVLTree::RemoveInorder(Node* node, int n) {
	if (node == nullptr)
		return;
	RemoveInorder(node->left, n);
	if (n == 0) {
		Remove(node->ufid);
		return;
	}
	RemoveInorder(node->right, n - 1);
}