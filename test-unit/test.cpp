#include "../src/main.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("Insert Incorrect Commands", "[incorect]"){

	AVLTree tree;
	tree.Insert("A11y", "45679999");
	tree.Insert("Fr3d", "10101010");
	tree.Insert("Hi Mom!", "13370000");
	tree.Insert("Dog", "Woofwoof");
	tree.Insert("Birds arent real", "1234567");
	std::vector<string> actualOutput = tree.PrintInorder();
	std::vector<string> expectedOutput = {};
	REQUIRE(expectedOutput.size() == actualOutput.size());
	REQUIRE(actualOutput == expectedOutput);
	
	REQUIRE(1 == 1);
}

TEST_CASE("Edge Cases", "[edge]") {

	AVLTree tree;
	tree.Remove("Briathan", "12345678");
	tree.RemoveInorder(13);
	tree.SearchID("00000000");
	std::vector<string> actualOutput = tree.PrintInorder();
	std::vector<string> expectedOutput = {};
	REQUIRE(expectedOutput.size() == actualOutput.size());
	REQUIRE(actualOutput == expectedOutput);

	REQUIRE(1 == 1);
}

TEST_CASE("Rotation Cases", "[rotate]") {

	AVLTree tree;
	tree.Insert("two", "22222222");
	tree.Insert("three", "333333333");
	tree.Insert("four", "44444444");
	tree.Insert("one", "11111111");
	tree.Insert("zero", "00000000");
	tree.Insert("nine", "99999999");
	tree.Insert("six", "66666666");
	tree.Insert("seven", "77777777");
	tree.Insert("eight", "88888888");
	std::vector<string> actualOutput = tree.PrintPreorder();
	std::vector<string> expectedOutput = { "three", "one", "zero", "two", "six", "four", "eight", "seven", "nine"};
	REQUIRE(expectedOutput.size() == actualOutput.size());
	REQUIRE(actualOutput == expectedOutput);

	REQUIRE(1 == 1);
}

TEST_CASE("Deletion Cases", "[delete]") {

	AVLTree tree;
	tree.Insert("five", "55555555");
	tree.Remove("55555555");
	tree.Insert("four", "44444444");
	tree.Insert("three", "33333333");
	tree.Insert("six", "66666666");
	tree.Insert("eight", "88888888");
	tree.Remove("66666666");
	tree.Insert("seven", "77777777");
	tree.Insert("nine", "99999999");
	tree.Remove("88888888");
	std::vector<string> actualOutput = tree.PrintPreorder();
	std::vector<string> expectedOutput = { "four", "three", "seven", "nine" };
	REQUIRE(expectedOutput.size() == actualOutput.size());
	REQUIRE(actualOutput == expectedOutput);

	REQUIRE(1 == 1);
}

TEST_CASE("Insert/Delete Large", "[large]") {

	AVLTree tree;
	std::vector<int> expectedOutput, actualOutput;

	for (int i = 0; i < 100; i++) {
		int randomInput = rand();
		if (std::count(expectedOutput.begin(), expectedOutput.end(), randomInput) == 0) {
			expectedOutput.push_back(randomInput);
			tree.Insert(randomInput);
		}
	}

	for (int i = 0; i < 100; i++) {
		int randomInput = rand();
		if (std::count(expectedOutput.begin(), expectedOutput.end(), randomInput) == 0) {
			expectedOutput.push_back(randomInput);
			tree.Insert(randomInput);
		}
	}

	actualOutput = tree.printInorder();
	REQUIRE(expectedOutput.size() == actualOutput.size());
	std::sort(expectedOutput.begin(), expectedOutput.end());
	REQUIRE(expectedOutput == actualOutput);

	REQUIRE(1 == 1);
}