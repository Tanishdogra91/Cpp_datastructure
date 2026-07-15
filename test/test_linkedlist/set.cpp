#include "linkedlist.h"
#include <gtest/gtest.h>
#include <stdexcept>

// Test 1: Set at valid indices
TEST(LinkedListSetTest, SetValid) {
  LinkedList<int> list;
  list.insertBack(10);
  list.insertBack(20);
  list.insertBack(30);

  list.set(0, 11);
  list.set(1, 22);
  list.set(2, 33);

  EXPECT_EQ(list.get(0), 11);
  EXPECT_EQ(list.get(1), 22);
  EXPECT_EQ(list.get(2), 33);
}

// Test 2: Set at invalid indices throws
TEST(LinkedListSetTest, SetInvalid) {
  LinkedList<int> list;
  EXPECT_THROW(list.set(-1, 5), std::out_of_range);
  EXPECT_THROW(list.set(0, 5), std::out_of_range);

  list.insertBack(10);
  EXPECT_THROW(list.set(1, 5), std::out_of_range);
}
