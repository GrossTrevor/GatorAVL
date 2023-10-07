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

## Worst Case Time Complexities

Insert(string name, string ufid) – O(log (n))

The insert function calls the InsertHelper() function that recursively moves through the tree and, since
the tree is binary, it ignores half of the tree each 􀆟me by comparing the ufids of the current node and
the potential next nodes. There are no loops and InsertHelper() only calls ShiftLeft() and ShiftRight(),
which are of constant time complexity.


Remove(string ufid) – O(n log (n))

The remove function calls the RemoveHelper() function that recursively moves through the tree and,
since the tree is binary, it ignores half of the tree each time by comparing the ufids of the current node
and the potential next nodes. There is one loop that only runs if the node to be deleted has two children,
and if that node’s left child has more left children, increasing the worst case complexity to O(n log(n))
instead of O(log (n)) like Insert().


SearchName(string name) – O(n)

The search name function calls the SearchNameHelper() function that traverses the entire tree in order,
printing out the ufids of the matching names as it comes across them. Since the entire tree is traversed,
the complexity is linear.


SearchID(string ufid) – O(log (n))

The search id function calls the SearchIDHelper() function that recursively moves through the tree and,
since the tree is binary, it ignores half of the tree each time by comparing the ufids of the current node
and the potential next nodes. There are no loops, meaning the complexity must be logarithmic.


PrintInorder() – O(n)

The print in order function calls the PrintInorderHelper() func􀆟on that recursively traverses the entire
tree in order, printing out the names as it comes across them. Since the entire tree is traversed, the
complexity is linear.


PrintPreorder() – O(n)

The print preorder function calls the PrintPreorderHelper() function that recursively traverses the entire
tree in preorder, printing out the names as it comes across them. Since the entire tree is traversed, the
complexity is linear.


PrintPostorder() – O(n)

The print postorder function calls the PrintPostorderHelper() function that recursively traverses the
entire tree in postorder, printing out the names as it comes across them. Since the entire tree is
traversed, the complexity is linear.


PrintLevelCount() – O(n)

The print level count functon calls the PrintLevelCountHelper() function that loops through the entire
tree while counting every possible location of a node until it reaches the maximum for that level, then
moves to the next level. The farther that this code executes, the greater the level count that is output.
Since the function must traverse the entire tree, the complexity in linear.


RemoveInorder(int n) – O(n2 log(n))

The remove in order function calls the RemoveInorderHelper() function that recursively traverses the
tree in order until it reaches the correct node position based on the input, then it deletes the selected
node by calling Remove(). Since this function works under the same logic as PrintInorder() by recursively
moving though the entire tree, the distance needed to travel is entire dependent on n, so the complexity
is at least linear. However, since RemoveInorderHelper() calls Remove() to delete the selected node, the
complexity of Remove() must also be counted, increasing the complexity to O(n2 log(n)).

## What did you learn from this assignment and what would you do differently if you had to start over?

Obviously, I learned a lot about the inner workings of the AVL Tree data structure and, by extension,
trees as a whole. This helped me to understand the usability of tree data structures in applications that
require the user to access data via a starting connection point (e.g. the root). This, like the Minesweeper
project from Prog. 2, also helped a lot with my comfortability with pointers as they are an integral part of
programming, especially in C++. Furthermore, this project helped me with testing, something that I was
definitely lacking in my previous programming works. If I had to start over, I would: A) start earlier,
because the past couple of nights have been stressful, B) think recursively from the get-go, because I had
to go back through and recurs-ify my functions to make them run with better complexities, and C) ensure
that memory management is done properly and I do not leave public locations open, another thing I had
to go back and fix, taking a lot of extra time. Overall, a very cool project, akin to the LinkedList, but a
great added level of complexity with the balancing.