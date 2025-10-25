/* ************************************************************************
> File Name:     src/IntBST.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 16:41:11 2025
> Description:   
 ************************************************************************/

#include "../include/IntBST.h"
#include <iostream>

IntBST::IntBST() : root(nullptr) {}

// Time: O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
IntBST::~IntBST() {
    destroyRecursive(root);
}

// Time: O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
void IntBST::destroyRecursive(IntNode* node) {
    if (node != nullptr) {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

// Time: Average O(log N), Worst O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
void IntBST::insert(int data) {
    root = insertRecursive(root, data);
}

// Time: Average O(log N), Worst O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
IntNode* IntBST::insertRecursive(IntNode* node, int data) {
    if (node == nullptr) {
        return new IntNode(data);
    }

    if (data < node->data) {
        node->left = insertRecursive(node->left, data);
    } else if (data > node->data) {
        node->right = insertRecursive(node->right, data);
    } else {
        std::cerr << "[warning] duplicate node ignored: " << node->data << std::endl;
    }
    
    return node;
}

// Time: O(N)
// Space: O(N) for result vector + O(H) for recursion stack depth (H = height of tree)
std::vector<int> IntBST::getInOrderValues() const {
    std::vector<int> result;
    inOrderRecursive(root, result);
    return result;
}

// Time: O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
void IntBST::inOrderRecursive(IntNode* node, std::vector<int>& result) const {
    if (node != nullptr) {
        inOrderRecursive(node->left, result);
        result.push_back(node->data);
        inOrderRecursive(node->right, result);
    }
}

// Time: O(1)
// Space: O(1)
bool IntBST::empty() const {
    return root == nullptr;
}
