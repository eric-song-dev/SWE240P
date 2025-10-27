/* ************************************************************************
> File Name:     include/BST.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 02:32:29 2025
> Description:   
 ************************************************************************/

#pragma once

#include "Node.h"
#include "Student.h"
#include <string>
#include <vector>
#include <fstream>
#include <queue>

class BST {
public:
    BST();
    ~BST();

    // Task 1: Insertion and Deletion
    void insert(Student data);
    void remove(const std::string& lastName);
    
    // Task 2: Pre-order Traversal (Depth-First)
    void preOrderTraversal(std::ofstream& outFile) const;

    // Task 2: In-order Traversal (Depth-First)
    void inOrderTraversal(std::ofstream& outFile) const;
    
    // Task 2: Post-order Traversal (Depth-First)
    void postOrderTraversal(std::ofstream& outFile) const;

    // Task 3: Level-order Traversal (Breadth-First)
    void levelOrderTraversal(std::ofstream& outFile) const;

    // Helper function to find a node
    Node* search(const std::string& lastName) const;

    // Helper function to check if tree is empty
    bool empty() const;

private:
    Node* root;

    // Recursive helper functions
    Node* insertRecursive(Node* node, Student data);
    Node* removeRecursive(Node* node, const std::string& lastName);
    Node* findMinNode(Node* node);
    void destroyRecursive(Node* node);
    void preOrderRecursive(Node* node, std::ofstream& outFile) const;
    void inOrderRecursive(Node* node, std::ofstream& outFile) const;
    void postOrderRecursive(Node* node, std::ofstream& outFile) const;
    Node* searchRecursive(Node* node, const std::string& lastName) const;
};
