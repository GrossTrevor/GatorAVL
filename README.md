### GatorAVL
# University of Florida COP 3530 Project 1

## Problem Statement

Binary Search Trees (BST) can often be an efficient and useful way to store and retrieve sorted data. However, the efficiency of these data trees relies heavily on how balanced a BST is. For example, searching through the BST on the left is much more efficient than searching through the BST on the right, despite both figures showing valid BST with the exact same elements.

To avoid inefficient binary search trees, we use balanced Binary Search Trees.  A balanced BST has a balance factor of less than ±threshold, where the balance factor is the difference in heights of the left and right subtrees at any given tree node. One such balanced tree is an AVL tree that maintains a threshold of 1. As soon as a node in an AVL tree has a balance factor of +2/-2, “tree rotations” are performed to maintain balance in the tree.

In this project, you will be designing a custom AVL tree to organize UF student accounts based on GatorIDs. You will build methods for insertion, deletion, search, and traversals for an AVL tree data structure. These methods would be called based on certain commands that are invoked in the main method. You are responsible for 

- 	Designing the interface/modules/functions of the standard AVL Tree and the operations required to execute the respective commands.
-	Parsing the input and ensuring data and command validation,
-	Building the main function to parse the inputs and calling the respective functions to match the output.
-	Testing your code within the constraints.

## Important Instructions

1. You can code your project in *src* directory. Feel free to create any header files and cpp files for your implementation. 

2. You are recommended to test your own code by building unit tests in *test-unit/test.cpp*
    - To run the tests, use the following command, 
        `g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test`
    - You will have to comment main() when unit testing your code because catch uses its own main().

3. You will submit the all files in src folder on Gradescope to test your code. If you are using multiple header files, you will have to include them directly in main.cpp once you are done with all your testing. **Remember, your code must pass tests on Gradescope to receive credit.**

4. Instructions on how to test io based tests through command line are given in *test-io/readme-io.md*.