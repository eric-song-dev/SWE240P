/* ************************************************************************
> File Name:     src/HeapBuilder.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 16:40:15 2025
> Description:   
 ************************************************************************/

#include "../include/HeapBuilder.h"
#include <vector>
#include <queue>
#include <stdexcept>
#include <algorithm>

HeapBuilder::HeapBuilder() {}

HeapBuilder::~HeapBuilder() {}

// Time: O(N) - buildTree O(N) + minHeapify O(N)
// Space: O(N)
Node* HeapBuilder::createMinHeap(const std::vector<int>& values) {
    if (values.empty()) {
        return nullptr;
    }
    // 1. Build the binary tree structure, complete binary tree
    Node* root = buildTreeLevelOrder(values);

    // 2. Heapify the tree, turn it into a min-heap
    minHeapify(root);

    return root;
}

// Time: O(N) - buildTree O(N) + maxHeapify O(N)
// Space: O(N)
Node* HeapBuilder::createMaxHeap(const std::vector<int>& values) {
    if (values.empty()) {
        return nullptr;
    }
    // 1. Build the binary tree structure, complete binary tree
    Node* root = buildTreeLevelOrder(values);

    // 2. Heapify the tree, turn it into a max-heap
    maxHeapify(root);

    return root;
}

// Helper to build a complete binary tree structure from vector level by level
// Time: O(N), where N is the number of values
// Space: O(N + W_max), where N is the number of values, W_max is max width of complete binary tree
Node* HeapBuilder::buildTreeLevelOrder(const std::vector<int>& values) {
    if (values.empty()) {
        return nullptr;
    }

    Node* root = new Node(values[0]);
    std::queue<Node*> q;
    q.push(root);

    int i = 1;
    while (i < values.size()) {
        Node* current = q.front();
        q.pop();

        // Add left child
        current->left = new Node(values[i++]);
        q.push(current->left);

        // Add right child
        if (i < values.size()) {
            current->right = new Node(values[i++]);
            q.push(current->right);
        }
    }
    return root;
}

// Recursively applies siftDownMax starting from the leaves up, post-order traversal
// Time: O(N)
// Space: O(H) for recursion stack depth (H = height of tree or log N for complete binary tree)
void HeapBuilder::maxHeapify(Node* node) {
    if (node == nullptr) {
        return;
    }
    // Heapify children first, post-order traversal, bottom-up approach
    maxHeapify(node->left);
    maxHeapify(node->right);
    siftDownMax(node);
}

// Recursively applies siftDownMin starting from the leaves up, post-order traversal
// Time: O(N)
// Space: O(H) for recursion stack depth (H = height of tree or log N for complete binary tree)
void HeapBuilder::minHeapify(Node* node) {
    if (node == nullptr) {
        return;
    }
    // Heapify children first, post-order traversal, bottom-up approach
    minHeapify(node->left);
    minHeapify(node->right);
    siftDownMin(node);
}

// Time: O(log N), where N is the number of nodes
// Space: O(H) for recursion stack depth (H = height of tree or log N for complete binary tree)
void HeapBuilder::siftDownMax(Node* node) {
    if (node == nullptr) return;

    Node* largest = node;
    Node* left = node->left;
    Node* right = node->right;

    // Find the largest among node, left child, and right child
    if (left != nullptr && left->data > largest->data) {
        largest = left;
    }
    if (right != nullptr && right->data > largest->data) {
        largest = right;
    }

    // If largest is not the current node, swap and recurse
    if (largest != node) {
        std::swap(node->data, largest->data);
        siftDownMax(largest);
    }
}

// Time: O(log N), where N is the number of nodes
// Space: O(H) for recursion stack depth (H = height of tree or log N for complete binary tree)
void HeapBuilder::siftDownMin(Node* node) {
    if (node == nullptr) return;

    Node* smallest = node;
    Node* left = node->left;
    Node* right = node->right;

    // Find the smallest among node, left child, and right child
    if (left != nullptr && left->data < smallest->data) {
        smallest = left;
    }
    if (right != nullptr && right->data < smallest->data) {
        smallest = right;
    }

    // If smallest is not the current node, swap and recurse
    if (smallest != node) {
        std::swap(node->data, smallest->data);
        siftDownMin(smallest);
    }
}

void HeapBuilder::destroyTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}
