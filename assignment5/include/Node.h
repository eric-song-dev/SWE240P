/* ************************************************************************
> File Name:     include/Node.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 16:39:43 2025
> Description:   
 ************************************************************************/

#pragma once

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int data) : data(data), left(nullptr), right(nullptr) {}
    ~Node() {}
};
