/* ************************************************************************
> File Name:     tests/heap_test.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 16:42:14 2025
> Description:   
 ************************************************************************/

#include <gtest/gtest.h>
#include "HeapBuilder.h"
#include "BSTToHeapTransformer.h"
#include "IntBST.h"
#include "Node.h"
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

std::vector<int> getLevelOrder(Node* root) {
    std::vector<int> result;
    if (!root) return result;
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        result.push_back(current->data);
        if (current->left) q.push(current->left);
        if (current->right) q.push(current->right);
    }
    return result;
}

void deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

class Assignment5Test : public ::testing::Test {
protected:
    HeapBuilder builder;
    BSTToHeapTransformer transformer;

    bool isMinHeap(Node* node) {
        if (node == nullptr) return true;
        if (node->left && node->left->data < node->data) return false;
        if (node->right && node->right->data < node->data) return false;
        return isMinHeap(node->left) && isMinHeap(node->right);
    }

    bool isMaxHeap(Node* node) {
        if (node == nullptr) return true;
        if (node->left && node->left->data > node->data) return false;
        if (node->right && node->right->data > node->data) return false;
        return isMaxHeap(node->left) && isMaxHeap(node->right);
    }

    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(Assignment5Test, Task1_CreateMinHeap_Basic) {
    std::vector<int> values = {10, 5, 12, 3, 8, 15};
    Node* root = builder.createMinHeap(values);
    ASSERT_NE(root, nullptr);

    std::vector<int> levelOrder = getLevelOrder(root);
    EXPECT_EQ(root->data, 3); // Minimum element at root
    EXPECT_TRUE(isMinHeap(root)); // Verify heap property

    std::cout << "Min-Heap Level Order: ";
    for(int val : levelOrder) std::cout << val << " ";
    std::cout << std::endl;

    deleteTree(root);
    std::cout << "Test Passed: Min-Heap created correctly." << std::endl << std::endl;
}

TEST_F(Assignment5Test, Task1_CreateMaxHeap_Basic) {
    std::vector<int> values = {10, 5, 12, 3, 8, 15};
    Node* root = builder.createMaxHeap(values);
    ASSERT_NE(root, nullptr);

    std::vector<int> levelOrder = getLevelOrder(root);
    EXPECT_EQ(root->data, 15); // Maximum element at root
    EXPECT_TRUE(isMaxHeap(root)); // Verify heap property

    std::cout << "Max-Heap Level Order: ";
    for(int val : levelOrder) std::cout << val << " ";
    std::cout << std::endl;

    deleteTree(root);
    std::cout << "Test Passed: Max-Heap created correctly." << std::endl << std::endl;
}

TEST_F(Assignment5Test, Task1_CreateMinHeap_Empty) {
    std::vector<int> values = {};
    Node* root = builder.createMinHeap(values);
    EXPECT_EQ(root, nullptr);
    std::cout << "Test Passed: Empty input handled." << std::endl << std::endl;

}

TEST_F(Assignment5Test, Task1_CreateMaxHeap_Single) {
    std::vector<int> values = {42};
    Node* root = builder.createMaxHeap(values);
    ASSERT_NE(root, nullptr);
    EXPECT_EQ(root->data, 42);
    EXPECT_EQ(root->left, nullptr);
    EXPECT_EQ(root->right, nullptr);
    EXPECT_TRUE(isMaxHeap(root));
    deleteTree(root);
    std::cout << "Test Passed: Single element handled." << std::endl << std::endl;
}

TEST_F(Assignment5Test, Task2_BSTToMinHeap) {
    IntBST bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);
    // In-order traversal of BST: 3, 5, 7, 10, 12, 15, 18

    Node* heapRoot = transformer.bstToMinHeap(bst);
    ASSERT_NE(heapRoot, nullptr);

    std::vector<int> levelOrder = getLevelOrder(heapRoot);
    EXPECT_EQ(heapRoot->data, 3); // Minimum element at root
    EXPECT_TRUE(isMinHeap(heapRoot)); // Verify heap property

    std::cout << "BST to Min-Heap Level Order: ";
    for(int val : levelOrder) std::cout << val << " ";
    std::cout << std::endl;

    deleteTree(heapRoot);
    std::cout << "Test Passed: BST transformed to Min-Heap." << std::endl << std::endl;
}

TEST_F(Assignment5Test, Task2_BSTToMaxHeap) {
    IntBST bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    bst.insert(18);
    // In-order traversal of BST: 3, 5, 7, 10, 12, 15, 18

    Node* heapRoot = transformer.bstToMaxHeap(bst);
    ASSERT_NE(heapRoot, nullptr);

    std::vector<int> levelOrder = getLevelOrder(heapRoot);
    EXPECT_EQ(heapRoot->data, 18); // Maximum element at root
    EXPECT_TRUE(isMaxHeap(heapRoot)); // Verify heap property

    std::cout << "BST to Max-Heap Level Order: ";
    for(int val : levelOrder) std::cout << val << " ";
    std::cout << std::endl;

    deleteTree(heapRoot);
    std::cout << "Test Passed: BST transformed to Max-Heap." << std::endl << std::endl;
}

TEST_F(Assignment5Test, Task2_EmptyBSTToHeap) {
    IntBST bst; // Empty BST
    Node* minHeapRoot = transformer.bstToMinHeap(bst);
    EXPECT_EQ(minHeapRoot, nullptr);
    Node* maxHeapRoot = transformer.bstToMaxHeap(bst);
    EXPECT_EQ(maxHeapRoot, nullptr);
    std::cout << "Test Passed: Empty BST transformation handled." << std::endl << std::endl;
}
