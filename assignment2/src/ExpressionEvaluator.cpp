/* ************************************************************************
> File Name:     ExpressionEvaluator.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Wed Oct 22 12:43:49 2025
> Description:   
 ************************************************************************/

#include "../include/ExpressionEvaluator.h"
#include <stdexcept>
#include <cctype>
#include <cmath>
#include <iostream>

ExpressionEvaluator::ExpressionEvaluator() {}

// Time: O(1)
// Space: O(1)
Precedence ExpressionEvaluator::getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return Precedence::LOW;
    }
    if (op == '*' || op == '/') {
        return Precedence::HIGH;
    }
    return Precedence::NONE;
}

// Time: O(1)
// Space: O(1)
void ExpressionEvaluator::applyOperation() {
    char op = operatorStack.pop();
    long long operand2 = operandStack.pop();
    long long operand1 = operandStack.pop();

    if (op == '+') {
        operandStack.push(operand1 + operand2);
    } else if (op == '-') {
        operandStack.push(operand1 - operand2);
    } else if (op == '*') {
        operandStack.push(operand1 * operand2);
    } else if (op == '/') {
        if (operand2 == 0) {
            throw std::runtime_error("division by zero");
        }
        operandStack.push(operand1 / operand2);
    }
}

// Time: O(N), where N is the length of the expression
// Space: O(N)
double ExpressionEvaluator::evaluate(const std::string& expression) {
    operandStack.clear();
    operatorStack.clear();

    try {
        bool expectOperand = true; // Handle unary minus

        for (int i = 0; i < expression.length(); ++i) {
            char c = expression[i];

            if (isspace(c)) {
                // 1. Ignore whitespace
                continue;
            } else if (isdigit(c) || (c == '-' && expectOperand)) {
                // 2. Parse a number (operand)
                long long num = 0;
                bool negative = (c == '-');
                if (negative) {
                    i++; // Move past the '-'
                }

                // Check if a digit follows the unary minus
                if (i >= expression.length() || !isdigit(expression[i])) {
                     throw std::runtime_error("invalid expression: unary minus not followed by digit");
                }

                while (i < expression.length() && isdigit(expression[i])) {
                    num = (num * 10) + (expression[i] - '0');
                    i++;
                }
                i--; // Since i++ one more time, so need i-- here

                operandStack.push(negative ? -num : num);
                expectOperand = false; // Just found an operand
            } else if (c == '+' || c == '-' || c == '*' || c == '/') {
                // 3. Parse an operator
                while (!operatorStack.empty()
                       && static_cast<int>(getPrecedence(operatorStack.peek())) >= static_cast<int>(getPrecedence(c))) {
                    applyOperation();
                }
                operatorStack.push(c);
                expectOperand = true; // Expect an operand next
            } else {
                // 4. Invalid character
                throw std::runtime_error("invalid character in expression");
            }
        }

        // 5. Apply remaining operations
        while (!operatorStack.empty()) {
            applyOperation();
        }

        // 6. Final result should be on the stack
        if (operandStack.size() != 1 || !operatorStack.empty()) {
            throw std::runtime_error("invalid expression format");
        }

        return static_cast<double>(operandStack.pop());
    } catch (const std::exception& e) {
        std::cerr << "[error] " << e.what() << std::endl;
        return NAN;
    }
}
