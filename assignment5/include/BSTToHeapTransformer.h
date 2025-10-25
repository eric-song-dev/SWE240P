/* ************************************************************************
> File Name:     include/BSTToHeapTransformer.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 16:41:24 2025
> Description:   
 ************************************************************************/

#pragma once

#include "IntBST.h"
#include "HeapBuilder.h"
#include "Node.h"
#include <vector>

class BSTToHeapTransformer {
public:
    BSTToHeapTransformer();
    ~BSTToHeapTransformer();

    // Task 2
    // Converts BST to Min-Heap, returns the root of the heap tree
    Node* bstToMinHeap(const IntBST& bst);

    // Converts BST to Max-Heap, returns the root of the heap tree
    Node* bstToMaxHeap(const IntBST& bst);
    
private:
    HeapBuilder heapBuilder;
};
