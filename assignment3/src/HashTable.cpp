/* ************************************************************************
> File Name:     src/HashTable.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Thu Oct 23 15:31:36 2025
> Description:   
 ************************************************************************/

#include "../include/HashTable.h"
#include <iostream>

// Time: O(M), where M is the initialSize
// Space: O(M)
HashTable::HashTable(size_t initialSize) : tableSize(initialSize), currentSize(0) {
    if (tableSize <= 0) {
        tableSize = DEFAULT_HASH_TABLE_SIZE;
    }
    table.resize(tableSize);
}

// Time: O(N+M), where N is number of elements, M is table size.
// Space: O(1)
HashTable::~HashTable() {}

// djb2 algorithm, from http://www.cse.yorku.ca/~oz/hash.html
// Time: O(K), where K is the length of the key string
// Space: O(1)
size_t HashTable::hash(const std::string& key) const {
    unsigned long long hashValue = 5381; // magic number
    for (char c : key) {
        // hash = hash * 33 + c
        hashValue = ((hashValue << 5) + hashValue) + static_cast<unsigned long long>(c);
    }
    return hashValue % tableSize;
}


// Time: Average O(K + N/M), Worst O(K + N) where N is number of elements, M is table size, K is key length.
// Space: O(1) average (if key doesn't exist, O(K) to store the key)
bool HashTable::insert(const std::string& key) {
    size_t index = hash(key);
    for (const std::string& existingKey : table[index]) {
        if (existingKey == key) {
            return false;
        }
    }
    table[index].push_front(key);
    currentSize++;
    return true;
}

// Time: Average O(K + N/M), Worst O(K + N) where N is number of elements, M is table size, K is key length.
// Space: O(1)
bool HashTable::contains(const std::string& key) const {
    size_t index = hash(key);
    for (const std::string& existingKey : table[index]) {
        if (existingKey == key) {
            return true;
        }
    }
    return false;
}

// Time: O(1)
// Space: O(1)
size_t HashTable::size() const {
    return currentSize;
}

// Time: O(N+M)
// Space: O(1) (reallocates internal vector to default size)
void HashTable::clear() {
    table.clear();
     if (tableSize == 0) {
        tableSize = DEFAULT_HASH_TABLE_SIZE;
    }
    table.resize(tableSize);
    currentSize = 0;
}
