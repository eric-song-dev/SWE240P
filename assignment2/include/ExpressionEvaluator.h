/* ************************************************************************
> File Name:     ExpressionEvaluator.h
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Wed Oct 22 12:43:31 2025
> Description:   
 ************************************************************************/

#pragma once

#include "Stack.h"
#include <string>

enum class Precedence : int {
    NONE = 0,
    LOW = 1,  // For + and -
    HIGH = 2  // For * and /
};

class ExpressionEvaluator {
public:
    ExpressionEvaluator();

    // Evaluates the arithmetic expression.
    // Returns the result, or NaN if the expression is invalid.
    double evaluate(const std::string& expression);
    
private:
    // Helper to check operator precedence
    // Returns true if op1 has higher or equal precedence than op2
    Precedence getPrecedence(char op);

    // Helper to apply an operation
    void applyOperation();

private:
    // Stacks
    Stack<long long> operandStack;
    Stack<char> operatorStack;
};
