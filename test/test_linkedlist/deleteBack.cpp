#include "linkedlist.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Test 1: Delete back on a list with single element
TEST(LinkedListDeleteBackTest, DeleteBackSingle) {
  LinkedList<int> list;
  list.insertBack(42);

  list.deleteBack();
  EXPECT_TRUE(list.isEmpty());
  EXPECT_EQ(list.size(), 0);
}

// Test 2: Delete back on a list with multiple elements
TEST(LinkedListDeleteBackTest, DeleteBackMultiple) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);
  list.insertBack(30);

  list.deleteBack();
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(list.get(0), 10);
  EXPECT_EQ(list.get(1), 20);

  list.deleteBack();
  EXPECT_EQ(list.size(), 1);
  EXPECT_EQ(list.get(0), 10);
}

// Test 3: Delete back on an empty list throws
TEST(LinkedListDeleteBackTest, DeleteBackEmpty) {
  LinkedList<int> list;
  EXPECT_THROW(list.deleteBack(), std::out_of_range);
}
