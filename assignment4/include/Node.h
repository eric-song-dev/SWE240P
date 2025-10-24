/* ************************************************************************
> File Name:     include/Node.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 02:32:01 2025
> Description:   
 ************************************************************************/

#pragma once

#include "Student.h"

struct Node {
    Student data;
    Node* left;
    Node* right;

    Node(Student studentData);
    ~Node();
};
