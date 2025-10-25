/* ************************************************************************
> File Name:     include/HeapBuilder.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 16:40:01 2025
> Description:   
 ************************************************************************/

#pragma once

#include "Node.h"
#include <vector>
#include <queue>
#include <algorithm>

class HeapBuilder {
public:
    HeapBuilder();
    ~HeapBuilder();

    // Task 1
    // Creates a Min-Heap and returns the root of the binary tree
    Node* createMinHeap(const std::vector<int>& values);

    // Creates a Max-Heap and returns the root of the binary tree
    Node* createMaxHeap(const std::vector<int>& values);
    
private:
    // Helper function to build a complete binary tree structure from vector level by level
    Node* buildTreeLevelOrder(const std::vector<int>& values);

    // Helper functions for heapifying the tree structure
    void maxHeapify(Node* node);
    void minHeapify(Node* node);

    // Recursive helpers to swap data down the tree to maintain heap property
    void siftDownMax(Node* node);
    void siftDownMin(Node* node);

    // Helper to destroy the tree
    void destroyTree(Node* node);
};
