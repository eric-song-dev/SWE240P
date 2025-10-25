/* ************************************************************************
> File Name:     include/IntBST.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 16:40:44 2025
> Description:   
 ************************************************************************/

#pragma once

#include <vector>
#include <stdexcept>

// Simple Node for IntBST
struct IntNode {
    int data;
    IntNode* left;
    IntNode* right;

    IntNode(int data) : data(data), left(nullptr), right(nullptr) {}
};

class IntBST {
private:
    IntNode* root;

    // Recursive helpers
    IntNode* insertRecursive(IntNode* node, int data);
    void destroyRecursive(IntNode* node);
    void inOrderRecursive(IntNode* node, std::vector<int>& result) const;

public:
    IntBST();
    ~IntBST();

    // Inserts an integer into the BST
    void insert(int data);

    // Performs an in-order traversal and returns the values in a vector
    std::vector<int> getInOrderValues() const;

    // Checks if the tree is empty
    bool empty() const;
};
