#include <iostream>
#include <string>
#include <vector>
#include "Node.h"
#include "Node.hpp"
#include "AVLTree.h"
#include "AVLTree.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::getline;
using std::stoi;

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

int main(){
	int numLines = 0;
	int index = 0;
	int i = 0;
	string line = "";
	string command = "";
	string name = "";
	string ufid = "";
	string n = "";
	bool isAlpha = true;
	bool isDigit = true;
	bool run = false;
	AVLTree tree;

	cin >> numLines;

	for (int j = 0; j < numLines; j++) {
		cin >> line;
		index = line.find(' ');

		if (index != -1) {
			command = line.substr(0, index);
			line = line.substr(index + 1);

			if (command == "insert") {
				index = line.find('\"');

				if (index != -1) {
					line = line.substr(index + 1);
					index = line.find('\"');

					if (index != -1) {
						name = line.substr(0, index);

						i = 0;
						while (name[i]) {
							if (!isalpha(name[i])) {
								isAlpha = false;
								break;
							}
							i++;
						}

						if (isAlpha) {
							line = line.substr(index + 1);
							index = line.find(' ');

							if (index != -1) {
								ufid = line.substr(index + 1);

								if (ufid.length() == 8) {

									i = 0;
									while (ufid[i]) {
										if (!isdigit(ufid[i])) {
											isDigit = false;
											break;
										}
										i++;
									}
									if (isDigit) {
										tree.Insert(name, ufid);
										run = true;
									}
									isDigit = true;
								}
							}
						}
						isAlpha = true;
					}
				}
			}

			else if (command == "remove") {
				index = line.find(' ');

				if (index != -1) {
					ufid = line.substr(index + 1);

					if (ufid.length() == 8) {

						i = 0;
						while (ufid[i]) {
							if (!isdigit(ufid[i])) {
								isDigit = false;
								break;
							}
							i++;
						}

						if (isDigit) {
							tree.Remove(ufid);
							run = true;
						}
						isDigit = true;
					}
				}
			}

			else if (command == "searchID") {
				index = line.find(' ');

				if (index != -1) {
					ufid = line.substr(index + 1);

					if (ufid.length() == 8) {

						i = 0;
						while (ufid[i]) {
							if (!isdigit(ufid[i])) {
								isDigit = false;
								break;
							}
							i++;
						}

						if (isDigit) {
							tree.SearchID(ufid);
							run = true;
						}
						isDigit = true;
					}
				}
			}

			else if (command == "searchName") {
				index = line.find('\"');

				if (index != -1) {
					line = line.substr(index + 1);
					index = line.find('\"');

					if (index != -1) {
						name = line.substr(0, index);

						i = 0;
						while (name[i]) {
							if (!isalpha(name[i])) {
								isAlpha = false;
								break;
							}
							i++;
						}

						if (isAlpha) {
							tree.SearchName(name);
							run = true;
						}
					}
				}
			}

			else if (command == "removeInorder") {
				n = line.substr(index + 1);

				i = 0;
				while (n[i]) {
					if (!isdigit(n[i])) {
						isDigit = false;
						break;
					}
					i++;
				}

				if (isDigit) {
					tree.RemoveInorder(stoi(n));
					run = true;
				}
				isDigit = true;
			}
		}

		else {
			command = line;

			if (command == "printInorder") {
				tree.PrintInorder();
				run = true;
			}

			else if (command == "printPreorder") {
				tree.PrintPreorder();
				run = true;
			}

			else if (command == "printPostorder") {
				tree.PrintPostorder();
				run = true;
			}

			else if (command == "printLevelCount") {
				tree.PrintLevelCount();
				run = true;
			}
		}

		if (!run) {
			cout << "unsuccessful" << endl;
		}
	}

	return 0;
}

