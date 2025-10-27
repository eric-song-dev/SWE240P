#include <gtest/gtest.h>
#include "Bank.h"

class BankTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(BankTest, Task1And2_AddUser) {
    std::cout << "--- Test (Task 1 & 2): addUser and Sorted List ---" << std::endl;
    Bank bank;
    bank.addUser("Charlie", "321 Oak St", "333-33-333", 300.0);
    bank.addUser("Alice", "123 Main St", "111-11-111", 100.0);
    bank.addUser("Bob", "456 Pine St", "222-22-222", 200.0);
    
    bank.printList();
    ASSERT_NE(bank.findUser(1), nullptr);
    EXPECT_EQ(bank.findUser(1)->name, "Charlie");
    ASSERT_NE(bank.findUser(2), nullptr);
    EXPECT_EQ(bank.findUser(2)->name, "Alice");
    ASSERT_NE(bank.findUser(3), nullptr);
    EXPECT_EQ(bank.findUser(3)->name, "Bob");
    std::cout << "Test Passed: Users added and list is sorted by ID." << std::endl << std::endl;
}

TEST_F(BankTest, Task3_DeleteAndRecycleID) {
    std::cout << "--- Test (Task 3): deleteUser and ID Recycling ---" << std::endl;
    Bank bank;
    bank.addUser("Alice", "123 Main St", "111-11-111", 100.0); // ID 1
    bank.addUser("Bob", "456 Pine St", "222-22-222", 200.0);   // ID 2
    
    std::cout << "Before deletion:" << std::endl;
    bank.printList();
    
    ASSERT_TRUE(bank.deleteUser(2)); // Delete Bob (ID 2)
    ASSERT_TRUE(bank.deleteUser(1)); // Delete Alice (ID 1)
    EXPECT_EQ(bank.findUser(1), nullptr);
    
    std::cout << "After deleting ID 2 and 1:" << std::endl;
    bank.printList();
    
    // Add new user, should get recycled ID 2
    auto david = bank.addUser("David", "789 Elm St", "444-44-444", 400.0);
    ASSERT_NE(david, nullptr);
    EXPECT_EQ(david->id, 2);
    
    std::cout << "After adding David (should get ID 1):" << std::endl;
    bank.printList();
    std::cout << "Test Passed: User deleted and ID 1 was recycled." << std::endl << std::endl;
}

TEST_F(BankTest, Task4_PayUserToUser) {
    std::cout << "--- Test (Task 4): payUserToUser ---" << std::endl;
    Bank bank;
    auto alice = bank.addUser("Alice", "123 Main St", "111-11-111", 150.0); // ID 1
    auto bob = bank.addUser("Bob", "456 Pine St", "222-22-222", 200.0);   // ID 2
    
    std::cout << "Before payment:" << std::endl;
    bank.printList();
    
    // Test 1: Successful payment
    bool success = bank.payUserToUser(1, 2, 50.0);
    ASSERT_TRUE(success);
    EXPECT_DOUBLE_EQ(alice->balance, 100.0);
    EXPECT_DOUBLE_EQ(bob->balance, 250.0);
    
    // Test 2: Insufficient funds
    bool fail = bank.payUserToUser(1, 2, 101.0);
    EXPECT_FALSE(fail);
    EXPECT_DOUBLE_EQ(alice->balance, 100.0); // Unchanged
    
    // Test 3: User not found
    bool fail_nouser = bank.payUserToUser(1, 99, 10.0);
    EXPECT_FALSE(fail_nouser);
    
    std::cout << "After payment attempts:" << std::endl;
    bank.printList();
    std::cout << "Test Passed: payUserToUser handles success and failures." << std::endl << std::endl;
}

TEST_F(BankTest, Task5_GetMedianID) {
    std::cout << "--- Test (Task 5): getMedianID ---" << std::endl;
    Bank bank;
    
    // Test 1: Odd number of users
    bank.addUser("User1", "...", "...", 10); // ID 1
    bank.addUser("User2", "...", "...", 10); // ID 2
    bank.addUser("User3", "...", "...", 10); // ID 3
    std::cout << "Odd list (IDs 1, 2, 3):" << std::endl;
    bank.printList();
    EXPECT_DOUBLE_EQ(bank.getMedianID(), 2.0);
    std::cout << "Median: " << bank.getMedianID() << std::endl;

    // Test 2: Even number of users
    bank.addUser("User4", "...", "...", 10); // ID 4
    std::cout << "Even list (IDs 1, 2, 3, 4):" << std::endl;
    bank.printList();
    // Median is avg of 2 and 3
    EXPECT_DOUBLE_EQ(bank.getMedianID(), 2.5);
    std::cout << "Median: " << bank.getMedianID() << std::endl;

    // Test 3: With recycled IDs
    bank.deleteUser(2);
    bank.deleteUser(3);
    auto user5 = bank.addUser("User5", "...", "...", 10); // Gets ID 2
    auto user6 = bank.addUser("User6", "...", "...", 10); // Gets ID 3
    EXPECT_EQ(user5->id, 2);
    EXPECT_EQ(user6->id, 3);
    std::cout << "Scrambled list (IDs 1, 2, 3, 4):" << std::endl;
    bank.printList();
    // List is sorted: 1, 2, 3, 4. Median is still avg of 2 and 3.
    EXPECT_DOUBLE_EQ(bank.getMedianID(), 2.5);
    std::cout << "Median: " << bank.getMedianID() << std::endl;
    
    std::cout << "Test Passed: getMedianID handles odd and even lists." << std::endl << std::endl;
}

TEST_F(BankTest, Task6_MergeAccounts) {
    std::cout << "--- Test (Task 6): mergeAccounts ---" << std::endl;
    Bank bank;
    bank.addUser("Jane Doe", "1 Market St", "999-99-999", 500.0); // ID 1
    bank.addUser("John Doe", "2 Main St", "888-88-888", 200.0); // ID 2
    bank.addUser("Jane Doe", "1 Market St", "999-99-999", 300.0); // ID 3
    
    std::cout << "Before merge:" << std::endl;
    bank.printList();

    // Test 1: Successful merge
    bool success = bank.mergeAccounts(1, 3);
    ASSERT_TRUE(success);
    
    std::cout << "After successful merge (1 and 3):" << std::endl;
    bank.printList();
    
    auto keptAcc = bank.findUser(1);
    ASSERT_NE(keptAcc, nullptr);
    EXPECT_DOUBLE_EQ(keptAcc->balance, 800.0); // 500 + 300
    EXPECT_EQ(bank.findUser(3), nullptr); // ID 3 deleted
    
    // Test 2: Failed merge (different users)
    bool fail = bank.mergeAccounts(1, 2);
    EXPECT_FALSE(fail);
    ASSERT_NE(bank.findUser(1), nullptr);
    EXPECT_DOUBLE_EQ(bank.findUser(1)->balance, 800.0); // Unchanged
    ASSERT_NE(bank.findUser(2), nullptr); // Unchanged

    std::cout << "Test Passed: mergeAccounts handles success and failure." << std::endl << std::endl;
}

TEST_F(BankTest, Task7_MergeBanks) {
    std::cout << "--- Test (Task 7): mergeBanks ---" << std::endl;
    Bank bankOfOrangeCounty;
    bankOfOrangeCounty.addUser("Alice", "123 Main St", "111-11-111", 100.0); // ID 1
    bankOfOrangeCounty.addUser("Bob", "456 Pine St", "222-22-222", 200.0);   // ID 2
    
    Bank bankOfLosAngeles;
    bankOfLosAngeles.addUser("Charlie", "321 Oak St", "333-33-333", 300.0); // ID 1 (Conflict -> 4)
    bankOfLosAngeles.addUser("David", "789 Elm St", "444-44-444", 400.0);   // ID 2 (Conflict -> 5)
    bankOfLosAngeles.addUser("Eve", "101 Maple St", "555-55-555", 500.0);   // ID 3
    
    std::cout << "Bank of Orange County:" << std::endl;
    bankOfOrangeCounty.printList();
    std::cout << "Bank of Los Angeles:" << std::endl;
    bankOfLosAngeles.printList();

    Bank bsc = Bank::mergeBanks(bankOfOrangeCounty, bankOfLosAngeles);
    
    std::cout << "New Bank of Southern California (Merged):" << std::endl;
    bsc.printList();
    
    ASSERT_NE(bsc.findUser(1), nullptr);
    EXPECT_EQ(bsc.findUser(1)->name, "Alice");
    ASSERT_NE(bsc.findUser(2), nullptr);
    EXPECT_EQ(bsc.findUser(2)->name, "Bob");
    ASSERT_NE(bsc.findUser(3), nullptr);
    EXPECT_EQ(bsc.findUser(3)->name, "Eve");
    ASSERT_NE(bsc.findUser(4), nullptr);
    EXPECT_EQ(bsc.findUser(4)->name, "Charlie");
    ASSERT_NE(bsc.findUser(5), nullptr);
    EXPECT_EQ(bsc.findUser(5)->name, "David");
    
    std::cout << "Test Passed: mergeBanks handles ID conflicts and creates sorted list." << std::endl << std::endl;
}
