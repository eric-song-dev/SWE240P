/* ************************************************************************
> File Name:     include/HashTable.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Thu Oct 23 15:29:09 2025
> Description:   
 ************************************************************************/

#pragma once

#include <vector>
#include <list>
#include <string>

static const size_t DEFAULT_HASH_TABLE_SIZE = 1000;

class HashTable {
public:
    HashTable(size_t initialSize = DEFAULT_HASH_TABLE_SIZE);

    ~HashTable();

    // Hash function to convert string to index
    size_t hash(const std::string& key) const;

    // Insert a string into the hash table.
    // Returns true if inserted, false otherwise.
    bool insert(const std::string& key);

    // Check if a key exists in the hash table.
    bool contains(const std::string& key) const;

    // Returns the number of unique keys in the hash table.
    size_t size() const;

    // Clear the hash table.
    void clear();

private:
    // Separate Chaining
    // Each slot in the hash table stores a linked list (or another structure) of all elements that hash to the same index
    // When a collision occurs, the new element is simply appended to the list at that position
    std::vector<std::list<std::string>> table;
    size_t tableSize;
    size_t currentSize;
};
