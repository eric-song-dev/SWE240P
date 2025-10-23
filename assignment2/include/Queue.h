/* ************************************************************************
> File Name:     Queue.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Wed Oct 22 01:03:23 2025
> Description:   
 ************************************************************************/

#pragma once

#include <list>
#include <stdexcept>

template <typename T>
class Queue {
public:
    Queue();
    ~Queue();

    // Enqueue element in the queue.
    void enqueue(T element);

    // Remove and return the earliest element from the queue.
    T dequeue();

    // Returns the earliest element without removing it.
    T poll() const;

    // Returns the size of the queue.
    int size() const;

    // Helper function to check if the queue is empty.
    bool empty() const;
    
    // Clear elements in the queue.
    void clear();

private:
    std::list<T> elements;
};

template <typename T>
Queue<T>::Queue() {}

template <typename T>
Queue<T>::~Queue() {}

// Time: O(1)
// Space: O(1)
template <typename T>
void Queue<T>::enqueue(T element) {
    elements.push_back(element);
}

// Time: O(1)
// Space: O(1)
template <typename T>
T Queue<T>::dequeue() {
    if (empty()) {
        throw std::runtime_error("queue is empty, cannot dequeue");
    }
    T frontElement = elements.front();
    elements.pop_front();
    return frontElement;
}

// Time: O(1)
// Space: O(1)
template <typename T>
T Queue<T>::poll() const {
    if (empty()) {
        throw std::runtime_error("queue is empty, cannot poll");
    }
    return elements.front();
}

// Time: O(1)
// Space: O(1)
template <typename T>
int Queue<T>::size() const {
    return static_cast<int>(elements.size());
}

// Time: O(1)
// Space: O(1)
template <typename T>
bool Queue<T>::empty() const {
    return elements.empty();
}

// Time: O(1)
// Space: O(1)
template <typename T>
void Queue<T>::clear() {
    elements.clear();
}
