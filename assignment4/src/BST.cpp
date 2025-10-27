/* ************************************************************************
> File Name:     src/BST.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 02:32:48 2025
> Description:   
 ************************************************************************/

#include "../include/BST.h"
#include <iostream>
#include <stdexcept>

BST::BST() : root(nullptr) {}

// Time: O(N), where N is the number of nodes
// Space: O(H) for recursion stack depth (H = height of tree)
BST::~BST() {
    destroyRecursive(root);
}

// Time: O(N), where N is the number of nodes
// Space: O(H) for recursion stack depth (H = height of tree)
void BST::destroyRecursive(Node* node) {
    if (node != nullptr) {
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

// Time: O(1)
// Space: O(1)
bool BST::empty() const {
    return root == nullptr;
}

// Time: Average O(log N), Worst O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
void BST::insert(Student data) {
    root = insertRecursive(root, data);
}

// Time: Average O(log N), Worst O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
Node* BST::insertRecursive(Node* node, Student data) {
    if (node == nullptr) {
        return new Node(data);
    }

    int comparison = data.compareLastName(node->data);

    if (comparison < 0) {
        node->left = insertRecursive(node->left, data);
    } else if (comparison > 0) {
        node->right = insertRecursive(node->right, data);
    } else {
        std::cerr << "[warning] duplicate last name ignored: " << data.lastName << std::endl;
    }
    return node;
}

// Time: Average O(log N), Worst O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
void BST::remove(const std::string& lastName) {
    root = removeRecursive(root, lastName);
}

// Helper to find the node with the minimum value (leftmost) in a subtree
// Time: O(H)
// Space: O(1) if iterative, O(H) if recursive
Node* BST::findMinNode(Node* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Time: Average O(log N), Worst O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
Node* BST::removeRecursive(Node* node, const std::string& lastName) {
    if (node == nullptr) {
        return nullptr;
    }

    int comparison = compareCaseInsensitive(lastName, node->data.lastName);

    if (comparison < 0) {
        node->left = removeRecursive(node->left, lastName);
    } else if (comparison > 0) {
        node->right = removeRecursive(node->right, lastName);
    } else {
        // Node found
        // Case 1: Node with only one child or no child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Case 2: Node with two children
        // Get the inorder successor (smallest in the right subtree)
        Node* temp = findMinNode(node->right);

        // Copy the inorder successor's content to this node
        node->data = temp->data;

        // Delete the inorder successor
        node->right = removeRecursive(node->right, temp->data.lastName);
    }
    return node;
}

// Time: Average O(log N), Worst O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
Node* BST::search(const std::string& lastName) const {
    return searchRecursive(root, lastName);
}

// Time: Average O(log N), Worst O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
Node* BST::searchRecursive(Node* node, const std::string& lastName) const {
    if (node == nullptr) {
        return nullptr;
    }

    int comparison = compareCaseInsensitive(lastName, node->data.lastName);

    if (comparison < 0) {
        return searchRecursive(node->left, lastName);
    } else if (comparison > 0) {
        return searchRecursive(node->right, lastName);
    } else {
        return node;
    }
}

// Time: O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
void BST::preOrderTraversal(std::ofstream& outFile) const {
    preOrderRecursive(root, outFile);
}

// Time: O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
void BST::preOrderRecursive(Node* node, std::ofstream& outFile) const {
    if (node != nullptr) {
        outFile << node->data << std::endl;
        preOrderRecursive(node->left, outFile);
        preOrderRecursive(node->right, outFile);
    }
}

// Time: O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
void BST::inOrderTraversal(std::ofstream& outFile) const {
    inOrderRecursive(root, outFile);
}

// Time: O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
void BST::inOrderRecursive(Node* node, std::ofstream& outFile) const {
    if (node != nullptr) {
        inOrderRecursive(node->left, outFile);
        outFile << node->data << std::endl;
        inOrderRecursive(node->right, outFile);
    }
}

// Time: O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
void BST::postOrderTraversal(std::ofstream& outFile) const {
    postOrderRecursive(root, outFile);
}

// Time: O(N)
// Space: O(H) for recursion stack depth (H = height of tree)
void BST::postOrderRecursive(Node* node, std::ofstream& outFile) const {
    if (node != nullptr) {
        postOrderRecursive(node->left, outFile);
        postOrderRecursive(node->right, outFile);
        outFile << node->data << std::endl;
    }
}

// Time: O(N)
// Space: O(W), where W is the maximum width of the tree (worst case O(N) for a complete tree)
void BST::levelOrderTraversal(std::ofstream& outFile) const {
    if (root == nullptr) {
        return;
    }

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        outFile << current->data << std::endl;

        if (current->left != nullptr) {
            q.push(current->left);
        }
        if (current->right != nullptr) {
            q.push(current->right);
        }
    }
}
