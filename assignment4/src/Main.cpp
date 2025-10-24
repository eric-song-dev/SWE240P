/* ************************************************************************
> File Name:     src/Main.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 02:33:46 2025
> Description:   
 ************************************************************************/

#include "../include/BST.h"
#include "../include/Student.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

// Define constants for record field lengths
static const size_t OP_CODE_LEN = 1;
static const size_t STUDENT_NUM_LEN = 7;
static const size_t LAST_NAME_LEN = 25;
static const size_t DEPT_LEN = 4;
static const size_t PROG_LEN = 4;
static const size_t YEAR_LEN = 1;
static const size_t TOTAL_LEN = OP_CODE_LEN + STUDENT_NUM_LEN + LAST_NAME_LEN + DEPT_LEN + PROG_LEN + YEAR_LEN;

static const std::string DEFAULT_PATH = "/Users/ericsong/Courses/SWE240P/assignment4/";
static const std::string DEFAULT_FILENAME = DEFAULT_PATH + "tree-input.txt";
static const std::string IN_ORDER_FILENAME = DEFAULT_PATH + "in_order_traversal.txt";
static const std::string LEVEL_ORDER_FILENAME = DEFAULT_PATH + "level_order_traversal.txt";

// Helper function to trim trailing whitespace from a string
void trimTrailingWhitespace(std::string &s) {
    s.erase(s.find_last_not_of(" \n\r\t") + 1);
}


int main(int argc, char* argv[]) {
    std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
    std::string inputFilename = DEFAULT_FILENAME;
    if (argc > 1) {
        inputFilename = argv[1];
    }
    
    std::string inOrderFilename = IN_ORDER_FILENAME;
    std::string levelOrderFilename = LEVEL_ORDER_FILENAME;

    std::ifstream inputFile(inputFilename);
    if (!inputFile.is_open()) {
        std::cerr << "[error] could not open input file: " << inputFilename << std::endl;
        return 1;
    }

    BST studentTree;
    std::string line;
    int lineNumber = 0;

    std::cout << "--- Processing Input File: " << inputFilename << " ---" << std::endl;

    while (std::getline(inputFile, line)) {
        lineNumber++;
        if (line.length() != TOTAL_LEN) {
            std::cerr << "[warning] Line " << lineNumber << " is wrong, skipping." << std::endl;
            continue;
        }

        try {
            char operationCode = line[0];
            std::string studentNumber = line.substr(OP_CODE_LEN, STUDENT_NUM_LEN);
            std::string lastName = line.substr(OP_CODE_LEN + STUDENT_NUM_LEN, LAST_NAME_LEN);
            std::string department = line.substr(OP_CODE_LEN + STUDENT_NUM_LEN + LAST_NAME_LEN, DEPT_LEN);
            std::string program = line.substr(OP_CODE_LEN + STUDENT_NUM_LEN + LAST_NAME_LEN + DEPT_LEN, PROG_LEN);
            char year = line[OP_CODE_LEN + STUDENT_NUM_LEN + LAST_NAME_LEN + DEPT_LEN + PROG_LEN];

            // Trim potential trailing whitespace from parsed fields, especially last name
            trimTrailingWhitespace(studentNumber);
            trimTrailingWhitespace(lastName);
            trimTrailingWhitespace(department);
            trimTrailingWhitespace(program);

            Student student(studentNumber, lastName, department, program, year);

            if (operationCode == 'I') {
                std::cout << "inserting: " << student << std::endl;
                studentTree.insert(student);
            } else if (operationCode == 'D') {
                std::cout << "deleting: " << lastName << std::endl;
                studentTree.remove(lastName);
            } else {
                std::cerr << "[warning] Line " << lineNumber << ": invalid operation code '" << operationCode << "', skipping." << std::endl;
            }
        } catch (const std::out_of_range& oor) {
            std::cerr << "[error] Line " << lineNumber << ": error parsing line - " << oor.what() << std::endl;
        } catch (...) {
             std::cerr << "[error] Line " << lineNumber << ": unknown error parsing line." << std::endl;
        }
    }
    inputFile.close();
    std::cout << "--- Finished Processing Input File ---" << std::endl << std::endl;

    // Task 2: In-order Traversal
    std::cout << "--- output in-order traversal, filename: " << inOrderFilename << " ---" << std::endl;
    std::ofstream inOrderFile(inOrderFilename);
    if (!inOrderFile.is_open()) {
        std::cerr << "[error] could not open output file: " << inOrderFilename << std::endl;
        return 1;
    }
    studentTree.inOrderTraversal(inOrderFile);
    inOrderFile.close();
    std::cout << "--- in-order traversal complete ---" << std::endl << std::endl;

    // Task 3: Level-order Traversal
    std::cout << "--- output level-order traversal, filename: " << levelOrderFilename << " ---" << std::endl;
    std::ofstream levelOrderFile(levelOrderFilename);
     if (!levelOrderFile.is_open()) {
        std::cerr << "[error] could not open output file: " << levelOrderFilename << std::endl;
        return 1;
    }
    studentTree.levelOrderTraversal(levelOrderFile);
    levelOrderFile.close();
    std::cout << "--- level-order traversal complete ---" << std::endl << std::endl;

    return 0;
}
