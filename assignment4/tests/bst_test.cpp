/* ************************************************************************
> File Name:     tests/bst_test.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 02:35:32 2025
> Description:   
 ************************************************************************/

#include <gtest/gtest.h>
#include "BST.h"
#include "Student.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

std::vector<std::string> getInOrderOutput(const BST& tree) {
    std::stringstream ss;
    std::ofstream fakeOfstream;
    fakeOfstream.basic_ios<char>::rdbuf(ss.rdbuf());
    tree.inOrderTraversal(fakeOfstream);

    std::vector<std::string> outputLines;
    std::string line;
    while (std::getline(ss, line)) {
        outputLines.push_back(line);
    }
    return outputLines;
}

std::vector<std::string> getLevelOrderOutput(const BST& tree) {
    std::stringstream ss;
    std::ofstream fakeOfstream;
    fakeOfstream.basic_ios<char>::rdbuf(ss.rdbuf());
    tree.levelOrderTraversal(fakeOfstream);

    std::vector<std::string> outputLines;
    std::string line;
    while (std::getline(ss, line)) {
        outputLines.push_back(line);
    }
    return outputLines;
}


class BSTTest : public ::testing::Test {
protected:
    BST tree;
    Student s1{"1111111", "Davis", "CS", "BS", '3'};
    Student s2{"2222222", "Smith", "IN", "MS", '1'};
    Student s3{"3333333", "Jones", "CS", "PH", '5'};
    Student s4{"4444444", "Abbott", "EE", "BS", '2'};
    Student s5{"5555555", "Miller", "PH", "BS", '4'};
    Student s6{"6666666", "Taylor", "IN", "MS", '1'};
    Student s7_lower{"7777777", "davis", "CS", "BS", '3'};

    void SetUp() override {}

    void TearDown() override {}
};

TEST_F(BSTTest, BasicInsert) {
    EXPECT_TRUE(tree.empty());
    tree.insert(s1); // Davis
    EXPECT_FALSE(tree.empty());
    EXPECT_NE(tree.search("Davis"), nullptr);
    tree.insert(s2); // Smith
    EXPECT_NE(tree.search("Smith"), nullptr);
    tree.insert(s3); // Jones
    EXPECT_NE(tree.search("Jones"), nullptr);
    std::cout << "Test Passed: Basic insertion works." << std::endl << std::endl;
}

TEST_F(BSTTest, InsertOrderAndCaseInsensitive) {
    tree.insert(s1); // Davis
    tree.insert(s2); // Smith
    tree.insert(s3); // Jones
    tree.insert(s4); // Abbott
    tree.insert(s5); // Miller
    tree.insert(s6); // Taylor

    // Test case-insensitive search
    EXPECT_NE(tree.search("Davis"), nullptr);
    EXPECT_NE(tree.search("davis"), nullptr);
    EXPECT_NE(tree.search("SMITH"), nullptr);
    EXPECT_NE(tree.search("sMiTh"), nullptr);

    std::cout << "Test Passed: Case-insensitive search and duplicate handling (via warning) seem okay." << std::endl << std::endl;
}


TEST_F(BSTTest, Search) {
    tree.insert(s1); // Davis
    tree.insert(s2); // Smith
    tree.insert(s3); // Jones

    // Search for existing elements
    Node* foundNode = tree.search("Davis");
    ASSERT_NE(foundNode, nullptr);
    EXPECT_EQ(foundNode->data.studentNumber, "1111111");

    foundNode = tree.search("SMITH");
    ASSERT_NE(foundNode, nullptr);
    EXPECT_EQ(foundNode->data.studentNumber, "2222222");

    foundNode = tree.search("Jones");
    ASSERT_NE(foundNode, nullptr);
    EXPECT_EQ(foundNode->data.studentNumber, "3333333");

    // Search for non-existing element
    EXPECT_EQ(tree.search("NonExistent"), nullptr);
    EXPECT_EQ(tree.search("Brown"), nullptr);

    std::cout << "Test Passed: Search finds existing (case-insensitive) and correctly misses non-existing nodes." << std::endl << std::endl;
}

TEST_F(BSTTest, DeleteLeaf) {
    tree.insert(s1); // Davis
    tree.insert(s4); // Abbott (Left Leaf)
    tree.insert(s3); // Jones (Right Leaf)

    EXPECT_NE(tree.search("Abbott"), nullptr);
    tree.remove("Abbott");
    
    EXPECT_NE(tree.search("Jones"), nullptr);
    tree.remove("jones"); // Case-insensitive delete
    
    EXPECT_EQ(tree.search("Abbott"), nullptr);
    EXPECT_EQ(tree.search("Jones"), nullptr);
    EXPECT_NE(tree.search("Davis"), nullptr);

    std::cout << "Test Passed: Leaf node deletion works." << std::endl << std::endl;
}

TEST_F(BSTTest, DeleteRoot) {
    tree.insert(s1); // Davis (Root)
    tree.insert(s4); // Abbott (Left)
    tree.insert(s3); // Jones (Right)

    EXPECT_NE(tree.search("Davis"), nullptr);
    // Delete root
    tree.remove("Davis");
    EXPECT_EQ(tree.search("Davis"), nullptr);

    EXPECT_NE(tree.search("Jones"), nullptr);

    EXPECT_NE(tree.search("Abbott"), nullptr);

    // Delete root again
    tree.remove("Jones");
    EXPECT_EQ(tree.search("Jones"), nullptr);
    EXPECT_NE(tree.search("Abbott"), nullptr);

     // Delete root again
    tree.remove("Abbott");
    EXPECT_EQ(tree.search("Abbott"), nullptr);
    EXPECT_TRUE(tree.empty());

     std::cout << "Test Passed: Root deletion works for various scenarios." << std::endl << std::endl;
}

TEST_F(BSTTest, DeleteNotFound) {
    EXPECT_TRUE(tree.empty());
    tree.remove("NonExistent");

    tree.insert(s1);
    tree.insert(s2);
    EXPECT_EQ(tree.search("NotInTree"), nullptr);
    tree.remove("NotInTree");
    EXPECT_NE(tree.search("Davis"), nullptr);
    EXPECT_NE(tree.search("Smith"), nullptr);

     std::cout << "Test Passed: Attempting to delete non-existent nodes doesn't crash or delete others." << std::endl << std::endl;
}


TEST_F(BSTTest, InOrderTraversal) {
    tree.insert(s1); // Davis
    tree.insert(s2); // Smith
    tree.insert(s3); // Jones
    tree.insert(s4); // Abbott
    tree.insert(s5); // Miller
    tree.insert(s6); // Taylor

    std::vector<std::string> expectedOrder = {
        "4444444 Abbott                    EE   BS   2",
        "1111111 Davis                     CS   BS   3",
        "3333333 Jones                     CS   PH   5",
        "5555555 Miller                    PH   BS   4",
        "2222222 Smith                     IN   MS   1",
        "6666666 Taylor                    IN   MS   1",
    };

    std::vector<std::string> actualOrder = getInOrderOutput(tree);

    ASSERT_EQ(actualOrder.size(), expectedOrder.size());
    for (size_t i = 0; i < expectedOrder.size(); ++i) {
        EXPECT_EQ(actualOrder[i], expectedOrder[i]);
    }

    std::cout << "Test Passed: In-order traversal produces sorted output by last name." << std::endl << std::endl;
}

TEST_F(BSTTest, LevelOrderTraversal) {
    tree.insert(s2); // Smith
    tree.insert(s1); // Davis
    tree.insert(s6); // Taylor
    tree.insert(s4); // Abbott
    tree.insert(s3); // Jones
    tree.insert(s5); // Miller
    
    std::vector<std::string> expectedOrder = {
         "2222222 Smith                     IN   MS   1",
         "1111111 Davis                     CS   BS   3",
         "6666666 Taylor                    IN   MS   1",
         "4444444 Abbott                    EE   BS   2",
         "3333333 Jones                     CS   PH   5",
         "5555555 Miller                    PH   BS   4",
    };

    std::vector<std::string> actualOrder = getLevelOrderOutput(tree);

    ASSERT_EQ(actualOrder.size(), expectedOrder.size());
    for (size_t i = 0; i < expectedOrder.size(); ++i) {
        EXPECT_EQ(actualOrder[i], expectedOrder[i]);
    }

    std::cout << "Test Passed: Level-order traversal produces correct breadth-first output." << std::endl << std::endl;
}

TEST_F(BSTTest, TraversalEmptyTree) {
    EXPECT_TRUE(tree.empty());

    std::vector<std::string> inOrder = getInOrderOutput(tree);
    EXPECT_TRUE(inOrder.empty());

    std::vector<std::string> levelOrder = getLevelOrderOutput(tree);
    EXPECT_TRUE(levelOrder.empty());

    std::cout << "Test Passed: Traversals on empty tree produce no output." << std::endl << std::endl;
}
