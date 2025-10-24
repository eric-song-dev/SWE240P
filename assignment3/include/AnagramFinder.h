/* ************************************************************************
> File Name:     include/AnagramFinder.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Thu Oct 23 15:35:52 2025
> Description:   
 ************************************************************************/

#pragma once

#include "HashTable.h"
#include <string>

static const int DEFAULT_LARGE_HASH_TABLE_SIZE = 20000;

class AnagramFinder {
public:
    AnagramFinder(size_t hashTableSize = DEFAULT_LARGE_HASH_TABLE_SIZE);

    // Processes the file to find and store unique anagram roots
    // Returns true on success, false on file open error
    bool processFile(const std::string& filename);

    // Returns the count of unique anagram roots found
    size_t countUniqueAnagramRoots() const;

private:
    HashTable uniqueAnagramRoots;

    // Helper function to get the anagram root (sorted word)
    void getAnagramRoot(std::string& word);
};
