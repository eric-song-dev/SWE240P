/* ************************************************************************
> File Name:     src/Node.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 02:32:15 2025
> Description:   
 ************************************************************************/

#include "../include/Node.h"

Node::Node(Student studentData) : data(studentData), left(nullptr), right(nullptr) {}
Node::~Node() {}
