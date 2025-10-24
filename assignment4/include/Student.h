/* ************************************************************************
> File Name:     include/Student.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Fri Oct 24 02:31:32 2025
> Description:   
 ************************************************************************/

#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

// useful for search/delete
// Time: O(N + M), where N is the length of s1, M is the length of s2
// Space: O(N + M), where N is the length of s1, M is the length of s2
inline int compareCaseInsensitive(const std::string& s1, const std::string& s2) {
    std::string s1Lower = s1;
    std::string s2Lower = s2;
    std::transform(s1Lower.begin(), s1Lower.end(), s1Lower.begin(), ::tolower);
    std::transform(s2Lower.begin(), s2Lower.end(), s2Lower.begin(), ::tolower);
    if (s1Lower < s2Lower) return -1;
    if (s1Lower > s2Lower) return 1;
    return 0;
}

struct Student {
    std::string studentNumber; // 7 chars
    std::string lastName;      // 25 chars
    std::string department;    // 4 chars
    std::string program;       // 4 chars
    char year;                 // 1 char

    Student(std::string num = "", std::string name = "", std::string dept = "", std::string prog = "", char yr = ' ')
        : studentNumber(num), lastName(name), department(dept), program(prog), year(yr) {}

    // Case-insensitive comparison based on last name
    int compareLastName(const Student& other) const {
        return compareCaseInsensitive(this->lastName, other.lastName);
    }

    bool operator<(const Student& other) const {
        return compareLastName(other) < 0;
    }

    bool operator>(const Student& other) const {
        return compareLastName(other) > 0;
    }

    bool operator==(const Student& other) const {
        return compareLastName(other) == 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << std::left << std::setw(7) << student.studentNumber << " "
           << std::setw(25) << student.lastName << " "
           << std::setw(4) << student.department << " "
           << std::setw(4) << student.program << " "
           << student.year;
        return os;
    }
};
