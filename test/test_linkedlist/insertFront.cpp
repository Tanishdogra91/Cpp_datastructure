#include "linkedlist.h"
#include <gtest/gtest.h>

// Test 1: Insert into empty list
TEST(LinkedListInsertFrontTest, InsertIntoEmpty) {
  LinkedList<int> list;
  list.insertFront(42);
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), 42);
}

// Test 2: Multiple insertions at front
TEST(LinkedListInsertFrontTest, InsertMultiple) {
  LinkedList<int> list;
  list.insertFront(10);
  list.insertFront(20);
  list.insertFront(30);

  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.get(0), 30);
  EXPECT_EQ(list.get(1), 20);
  EXPECT_EQ(list.get(2), 10);
}
