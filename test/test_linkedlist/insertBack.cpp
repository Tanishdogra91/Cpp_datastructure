#include "linkedlist.h"
#include <gtest/gtest.h>

// Test 1: Insert into empty list
TEST(LinkedListInsertBackTest, InsertIntoEmpty) {
  LinkedList<int> list;
  list.insertBack(42);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), 42);
}

// Test 2: Multiple insertions at back
TEST(LinkedListInsertBackTest, InsertMultiple) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);
  list.insertBack(30);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.get(0), 10);
  EXPECT_EQ(list.get(1), 20);
  EXPECT_EQ(list.get(2), 30);
}
