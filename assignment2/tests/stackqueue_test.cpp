#include <gtest/gtest.h>
#include <iostream>
#include <cmath>
#include "Stack.h"
#include "Queue.h"
#include "StackWithTwoQs.h"
#include "ExpressionEvaluator.h"

class Assignment2Test : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(Assignment2Test, Task1_StackOperations) {
    std::cout << "--- Test (Task 1): Stack Implementation ---" << std::endl;
    Stack<int> stack;
    
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    
    stack.push(10);
    stack.push(20);
    
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 2);
    
    EXPECT_EQ(stack.peek(), 20); // Peek should not remove
    EXPECT_EQ(stack.size(), 2);
    
    EXPECT_EQ(stack.pop(), 20);  // Pop should remove
    EXPECT_EQ(stack.size(), 1);
    
    EXPECT_EQ(stack.pop(), 10);
    EXPECT_EQ(stack.size(), 0);
    EXPECT_TRUE(stack.empty());
    
    // Test empty stack exceptions
    EXPECT_THROW(stack.pop(), std::runtime_error);
    EXPECT_THROW(stack.peek(), std::runtime_error);
    
    std::cout << "Test Passed: Stack operations (push, pop, peek, size) work correctly." << std::endl << std::endl;
}

TEST_F(Assignment2Test, Task2_ExpressionEvaluator) {
    std::cout << "--- Test (Task 2): Expression Evaluator ---" << std::endl;
    ExpressionEvaluator evaluator;
    
    // Test 1: Provided example
    EXPECT_DOUBLE_EQ(evaluator.evaluate("10 + 20 * 2"), 50.0);
    
    // Test 2: Whitespace
    EXPECT_DOUBLE_EQ(evaluator.evaluate("  100   - 10 * 2  "), 80.0);
    
    // Test 3: Precedence
    EXPECT_DOUBLE_EQ(evaluator.evaluate("10 * 2 + 20"), 40.0);
    
    // Test 4: Division
    EXPECT_DOUBLE_EQ(evaluator.evaluate("100 / 10 + 5 * 3"), 25.0);
    
    // Test 5: All operators
    EXPECT_DOUBLE_EQ(evaluator.evaluate("50 + 100 / 10 - 5 * 2"), 50.0);
    
    // Test 6: Unary minus (negative numbers)
    EXPECT_DOUBLE_EQ(evaluator.evaluate("-10 + 20"), 10.0);
    EXPECT_DOUBLE_EQ(evaluator.evaluate("10 * -5"), -50.0);
    EXPECT_DOUBLE_EQ(evaluator.evaluate("-100 / -10"), 10.0);

    // Test 7: Invalid expression
    EXPECT_TRUE(std::isnan(evaluator.evaluate("foo / 30 + 7")));
    EXPECT_TRUE(std::isnan(evaluator.evaluate("10 + * 5")));
    EXPECT_TRUE(std::isnan(evaluator.evaluate("10 + 5 5")));
    EXPECT_TRUE(std::isnan(evaluator.evaluate("- 10"))); // Operator expects operand before it

    // Test 8: Division by zero
    EXPECT_TRUE(std::isnan(evaluator.evaluate("100 / 0")));
    EXPECT_TRUE(std::isnan(evaluator.evaluate("5 + (10 / (5 - 5))")));
    
    std::cout << "Test Passed: Expression evaluator handles valid and invalid cases." << std::endl << std::endl;
}


TEST_F(Assignment2Test, Task3_QueueOperations) {
    std::cout << "--- Test (Task 3): Queue Implementation ---" << std::endl;
    Queue<std::string> queue;
    
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    
    queue.enqueue("A");
    queue.enqueue("B");
    
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 2);
    
    EXPECT_EQ(queue.poll(), "A"); // Poll should not remove
    EXPECT_EQ(queue.size(), 2);
    
    EXPECT_EQ(queue.dequeue(), "A"); // Dequeue should remove
    EXPECT_EQ(queue.size(), 1);
    
    EXPECT_EQ(queue.dequeue(), "B");
    EXPECT_EQ(queue.size(), 0);
    EXPECT_TRUE(queue.empty());
    
    // Test empty queue exceptions
    EXPECT_THROW(queue.dequeue(), std::runtime_error);
    EXPECT_THROW(queue.poll(), std::runtime_error);
    
    std::cout << "Test Passed: Queue operations (enqueue, dequeue, poll, size) work correctly." << std::endl << std::endl;
}

TEST_F(Assignment2Test, Task4_StackWithTwoQs) {
    std::cout << "--- Test (Task 4): Stack with Two Queues ---" << std::endl;
    StackWithTwoQs<int> stack;
    
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    
    stack.push(100);
    stack.push(200);
    stack.push(300);
    
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 3);
    
    EXPECT_EQ(stack.peek(), 300); // Peek should not remove
    EXPECT_EQ(stack.size(), 3);
    
    EXPECT_EQ(stack.pop(), 300);  // Pop should remove
    EXPECT_EQ(stack.size(), 2);
    
    EXPECT_EQ(stack.peek(), 200);
    EXPECT_EQ(stack.pop(), 200);
    
    EXPECT_EQ(stack.pop(), 100);
    EXPECT_EQ(stack.size(), 0);
    EXPECT_TRUE(stack.empty());
    
    // Test empty stack exceptions
    EXPECT_THROW(stack.pop(), std::runtime_error);
    EXPECT_THROW(stack.peek(), std::runtime_error);
    
    std::cout << "Test Passed: StackWithTwoQs operations (push, pop, peek, size) work correctly." << std::endl << std::endl;
}
