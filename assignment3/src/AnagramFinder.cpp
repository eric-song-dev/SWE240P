/* ************************************************************************
> File Name:     src/AnagramFinder.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Thu Oct 23 15:36:11 2025
> Description:   
 ************************************************************************/

#include "../include/AnagramFinder.h"
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>

AnagramFinder::AnagramFinder(size_t hashTableSize) : uniqueAnagramRoots(hashTableSize) {}

// Time: O(N log N) due to sorting, where N is the length of the cleaned word
// Space: O(1)
void AnagramFinder::getAnagramRoot(std::string& word) {
    std::sort(word.begin(), word.end());
}

// Time: O(M + L * (N log N)), where M is the total number of characters in the file, L is the number of words, and N is the average length of a word
// Space: O(C_max + W_max + U*L), where C_max is the longest line, W_max is the longest word, U is unique anagram roots, L is avg root length, U*L is for hash table
bool AnagramFinder::processFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "[error] could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        auto dummyLine = line + " ";
        std::string word;
        for (char c : dummyLine) {
            if (std::isalnum(static_cast<unsigned char>(c))) {
                word += std::tolower(static_cast<unsigned char>(c));
            } else {
                if (!word.empty()) {
                    getAnagramRoot(word);
                    if (!word.empty()) { // Don't insert empty strings if a word was purely delimiters
                       uniqueAnagramRoots.insert(word); // Consider time complexity of insert operation of hash table is O(1)
                    }
                    word.clear();
                }
            }
        }
    }

    inputFile.close();
    return true;
}

// Time: O(1)
// Space: O(1)
size_t AnagramFinder::countUniqueAnagramRoots() const {
    return uniqueAnagramRoots.size();
}
