/* ************************************************************************
> File Name:     Stack.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Wed Oct 22 01:03:04 2025
> Description:   
 ************************************************************************/

#pragma once

#include <vector>
#include <stdexcept>

template <typename T>
class Stack {
public:
    Stack();
    ~Stack();

    // Pushes element in the stack.
    void push(T element);

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
    std::vector<T> elements;
};

template <typename T>
Stack<T>::Stack() {}

template <typename T>
Stack<T>::~Stack() {}

// Time: O(1)
// Space: O(1)
template <typename T>
void Stack<T>::push(T element) {
    elements.push_back(element);
}

// Time: O(1)
// Space: O(1)
template <typename T>
T Stack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("stack is empty, cannot pop");
    }
    T topElement = elements.back();
    elements.pop_back();
    return topElement;
}

// Time: O(1)
// Space: O(1)
template <typename T>
T Stack<T>::peek() const {
    if (empty()) {
        throw std::runtime_error("stack is empty, cannot peek");
    }
    return elements.back();
}

// Time: O(1)
// Space: O(1)
template <typename T>
int Stack<T>::size() const {
    return static_cast<int>(elements.size());
}

// Time: O(1)
// Space: O(1)
template <typename T>
bool Stack<T>::empty() const {
    return elements.empty();
}

// Time: O(1)
// Space: O(1)
template <typename T>
void Stack<T>::clear() {
    elements.clear();
}
