/* ************************************************************************
> File Name:     src/Main.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Thu Oct 23 15:36:35 2025
> Description:   
 ************************************************************************/

#include "../include/AnagramFinder.h"
#include <iostream>
#include <fstream>
#include <string>

static const std::string DEFAULT_FILENAME = "/Users/ericsong/Courses/SWE240P/assignment3/pride-and-prejudice.txt";

int main(int argc, char* argv[]) {
    std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
    std::string filename = DEFAULT_FILENAME;
    if (argc > 1) {
       filename = argv[1];
    }

    // Create AnagramFinder with a reasonably large hash table size
    AnagramFinder finder(DEFAULT_LARGE_HASH_TABLE_SIZE);

    if (!finder.processFile(filename)) {
        std::cerr << "failed to process the file" << std::endl;
        return 1;
    }
    
    size_t count = finder.countUniqueAnagramRoots();
    std::cout << "number of unique anagram-root words found: " << count << std::endl;

    return 0;
}
