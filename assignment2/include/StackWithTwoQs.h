/* ************************************************************************
> File Name:     StackWithTwoQs.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Wed Oct 22 01:03:44 2025
> Description:   
 ************************************************************************/

#pragma once

#include "Queue.h"
#include <stdexcept>
#include <utility>

template <typename T>
class StackWithTwoQs {
public:
    StackWithTwoQs();
    ~StackWithTwoQs();

    // Pushes x in the stack.
    void push(T x);

    // Removes the latest element from the stack and returns it.
    T pop();

    // Returns the latest element from the stack without removing it.
    T peek() const;

    // Returns the size of the stack.
    int size() const;

    // Helper function to check if the stack is empty.
    bool empty() const;
    
    // Clear elements in the stack.
    void clear();

private:
    Queue<T> queueOne;
    Queue<T> queueTwo;
};

template <typename T>
StackWithTwoQs<T>::StackWithTwoQs() {}

template <typename T>
StackWithTwoQs<T>::~StackWithTwoQs() {}

// Time: O(N), where N is the number of elements in the stack
// Space: O(1)
template <typename T>
void StackWithTwoQs<T>::push(T x) {
    queueTwo.enqueue(x);
    while (!queueOne.empty()) {
        queueTwo.enqueue(queueOne.dequeue());
    }

    std::swap(queueTwo, queueOne);
}

// Time: O(1)
// Space: O(1)
template <typename T>
T StackWithTwoQs<T>::pop() {
    if (empty()) {
        throw std::runtime_error("stack is empty, cannot pop");
    }
    T topElement = queueOne.poll();
    queueOne.dequeue();
    return topElement;
}

// Time: O(1)
// Space: O(1)
template <typename T>
T StackWithTwoQs<T>::peek() const {
    if (empty()) {
        throw std::runtime_error("stack is empty, cannot top");
    }
    return queueOne.poll();
}

// Time: O(1)
// Space: O(1)
template <typename T>
int StackWithTwoQs<T>::size() const {
    return queueOne.size();
}

// Time: O(1)
// Space: O(1)
template <typename T>
bool StackWithTwoQs<T>::empty() const {
    return queueOne.empty();
}

// Time: O(1)
// Space: O(1)
template <typename T>
void StackWithTwoQs<T>::clear() {
    queueOne.clear();
}
