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

int main() {
	int index = 0;
	string numLinesS = "";
	string line = "";
	string command = "";
	string name = "";
	string ufid = "";
	string n = "";
	bool isAlpha = true;
	bool isDigit = true;
	bool run = false;
	AVLTree tree;

	//Get number of instructions
	getline(cin, numLinesS);
	int numLines = stoi(numLinesS);

	for (int i = 0; i < numLines; i++) {
		getline(cin, line);
		index = line.find(' ');

		if (index != -1) {
			command = line.substr(0, index);
			line = line.substr(index + 1);

			//Insert
			if (command == "insert") {
				index = line.find('\"');

				if (index != -1) {
					line = line.substr(index + 1);
					index = line.find('\"');

					if (index != -1) {
						name = line.substr(0, index);

						for (int j = 0; j < name.length(); j++) {
							if (isalpha(name[j]) == 0) {
								if (isspace(name[j]) == 0) {
									isAlpha = false;
									break;
								}
							}
						}

						if (isAlpha) {
							line = line.substr(index + 1);
							index = line.find(' ');

							if (index != -1) {
								ufid = line.substr(index + 1);

								if (ufid.length() == 8) {

									for (int j = 0; j < ufid.length(); j++) {
										if (isdigit(ufid[j]) == 0) {
											isDigit = false;
											break;
										}
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

			//Remove
			else if (command == "remove") {
				ufid = line;

				if (ufid.length() == 8) {

					for (int j = 0; j < ufid.length(); j++) {
						if (isdigit(ufid[j]) == 0) {
							isDigit = false;
							break;
						}
					}
					if (isDigit) {
						tree.Remove(ufid);
						run = true;
					}
					isDigit = true;
				}
			}

			//Search
			else if (command == "search") {
				index = line.find('\"');
				//SearchName
				if (index != -1) {
					line = line.substr(index + 1);
					index = line.find('\"');

					if (index != -1) {
						name = line.substr(0, index);

						for (int j = 0; j < name.length(); j++) {
							if (isalpha(name[j]) == 0) {
								if (isspace(name[j]) == 0) {
									isAlpha = false;
									break;
								}
							}
						}

						if (isAlpha) {
							tree.SearchName(name);
							run = true;
						}
						isAlpha = true;
					}
				}

				//SearchID
				if (index == -1) {
					ufid = line.substr(index + 1);

					if (ufid.length() == 8) {

						for (int j = 0; j < ufid.length(); j++) {
							if (isdigit(ufid[j]) == 0) {
								isDigit = false;
								break;
							}
						}

						if (isDigit) {
							tree.SearchID(ufid);
							run = true;
						}
						isDigit = true;
					}
				}
			}

			//RemoveInorder
			else if (command == "removeInorder") {
				n = line;

				for (int j = 0; j < n.length(); j++) {
					if (isdigit(n[j]) == 0) {
						isDigit = false;
						break;
					}
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

			//PrintInorder
			if (command == "printInorder") {
				tree.PrintInorder();
				run = true;
			}

			//PrintPreorder
			else if (command == "printPreorder") {
				tree.PrintPreorder();
				run = true;
			}

			//PrintPostorder
			else if (command == "printPostorder") {
				tree.PrintPostorder();
				run = true;
			}

			//PrintLevelCount
			else if (command == "printLevelCount") {
				tree.PrintLevelCount();
				run = true;
			}
		}

		//If no command was run successfully
		if (!run) {
			cout << "unsuccessful" << endl;
		}
		index = 0;
	}

	return 0;
}