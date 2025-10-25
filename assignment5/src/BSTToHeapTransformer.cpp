/* ************************************************************************
> File Name:     src/BSTToHeapTransformer.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 16:41:36 2025
> Description:   
 ************************************************************************/

#include "../include/BSTToHeapTransformer.h"
#include <vector>

BSTToHeapTransformer::BSTToHeapTransformer() {}

BSTToHeapTransformer::~BSTToHeapTransformer() {}

// Time: O(N), where N is the number of values, O(N) for traversal + O(N) for heap building
// Space: O(N)
Node* BSTToHeapTransformer::bstToMinHeap(const IntBST& bst) {
    // 1. Get sorted values from BST using in-order traversal
    std::vector<int> sortedValues = bst.getInOrderValues();

    // 2. Use HeapBuilder to create a Min-Heap from these values
    return heapBuilder.createMinHeap(sortedValues);
}

// Time: O(N), where N is the number of values, O(N) for traversal + O(N) for heap building
// Space: O(N)
Node* BSTToHeapTransformer::bstToMaxHeap(const IntBST& bst) {
    // 1. Get sorted values from BST using in-order traversal
    std::vector<int> sortedValues = bst.getInOrderValues();

    // 2. Use HeapBuilder to create a Max-Heap from these values
    return heapBuilder.createMaxHeap(sortedValues);
}
