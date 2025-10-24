/* ************************************************************************
> File Name:     tests/hashtable_test.cpp
> Author:        Zhenyu Song
> Mail:          zhenyus4@uci.edu
> Created Time:  Thu Oct 23 15:41:16 2025
> Description:   
 ************************************************************************/

#include <gtest/gtest.h>
#include "HashTable.h"
#include <string>
#include <vector>

class HashTableTest : public ::testing::Test {
protected:
    HashTable ht;
    HashTable small_ht; // For collision testing

    HashTableTest() : ht(100), small_ht(5) {}

    void SetUp() override {
        ht.clear();
        small_ht.clear();
    }
    void TearDown() override {}
};

TEST_F(HashTableTest, BasicInsertAndSize) {
    EXPECT_EQ(ht.size(), 0);
    EXPECT_TRUE(ht.insert("apple"));
    EXPECT_EQ(ht.size(), 1);
    EXPECT_TRUE(ht.insert("banana"));
    EXPECT_EQ(ht.size(), 2);
    EXPECT_TRUE(ht.insert("cherry"));
    EXPECT_EQ(ht.size(), 3);
}

TEST_F(HashTableTest, DuplicateInsert) {
    EXPECT_TRUE(ht.insert("apple"));
    EXPECT_EQ(ht.size(), 1);
    EXPECT_FALSE(ht.insert("apple")); // Should return false for duplicate
    EXPECT_EQ(ht.size(), 1); // Size should not change
    EXPECT_TRUE(ht.insert("banana"));
    EXPECT_EQ(ht.size(), 2);
    EXPECT_FALSE(ht.insert("banana"));
    EXPECT_EQ(ht.size(), 2);
}

TEST_F(HashTableTest, Contains) {
    EXPECT_FALSE(ht.contains("apple"));
    ht.insert("apple");
    EXPECT_TRUE(ht.contains("apple"));
    ht.insert("banana");
    EXPECT_TRUE(ht.contains("banana"));
    EXPECT_FALSE(ht.contains("cherry"));
    ht.insert("cherry");
    EXPECT_TRUE(ht.contains("cherry"));
    EXPECT_TRUE(ht.contains("apple")); // Check again after more inserts
}

TEST_F(HashTableTest, Clear) {
    ht.insert("apple");
    ht.insert("banana");
    EXPECT_EQ(ht.size(), 2);
    EXPECT_TRUE(ht.contains("apple"));
    ht.clear();
    EXPECT_EQ(ht.size(), 0);
    EXPECT_FALSE(ht.contains("apple"));
    EXPECT_FALSE(ht.contains("banana"));
    // Test inserting after clearing
    EXPECT_TRUE(ht.insert("grape"));
    EXPECT_EQ(ht.size(), 1);
    EXPECT_TRUE(ht.contains("grape"));
}

TEST_F(HashTableTest, CollisionHandling) {
    EXPECT_TRUE(small_ht.insert("apple"));
    EXPECT_TRUE(small_ht.insert("banana"));
    EXPECT_TRUE(small_ht.insert("cherry"));
    EXPECT_TRUE(small_ht.insert("date"));
    EXPECT_TRUE(small_ht.insert("elderberry"));
    EXPECT_TRUE(small_ht.insert("fig"));
    EXPECT_TRUE(small_ht.insert("grape"));

    EXPECT_EQ(small_ht.size(), 7); // All unique strings should be inserted

    // Verify all inserted items can be found
    EXPECT_TRUE(small_ht.contains("apple"));
    EXPECT_TRUE(small_ht.contains("banana"));
    EXPECT_TRUE(small_ht.contains("cherry"));
    EXPECT_TRUE(small_ht.contains("date"));
    EXPECT_TRUE(small_ht.contains("elderberry"));
    EXPECT_TRUE(small_ht.contains("fig"));
    EXPECT_TRUE(small_ht.contains("grape"));

    // Test contains for non-existent item that might hash to same bucket
    EXPECT_FALSE(small_ht.contains("plum")); // Assume 'plum' hashes similarly to an existing item

    // Test duplicate insertion with collisions
    EXPECT_FALSE(small_ht.insert("apple"));
    EXPECT_FALSE(small_ht.insert("fig"));
    EXPECT_EQ(small_ht.size(), 7);
}

TEST_F(HashTableTest, EmptyString) {
    EXPECT_TRUE(ht.insert(""));
    EXPECT_EQ(ht.size(), 1);
    EXPECT_TRUE(ht.contains(""));
    EXPECT_FALSE(ht.insert(""));
    EXPECT_EQ(ht.size(), 1);
    ht.clear();
    EXPECT_EQ(ht.size(), 0);
    EXPECT_FALSE(ht.contains(""));
}
