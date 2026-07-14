#include "dynamicarray.h"
#include <gtest/gtest.h>

class TestObject {
public:
  static int destroyed;

  TestObject() = default;
  TestObject(const TestObject &) = default;

  ~TestObject() { destroyed++; }
};

int TestObject::destroyed = 0;

TEST(DynamicArrayDestructorTest, DestructorDestroysElements) {
  TestObject::destroyed = 0;

  {
    DynamicArray<TestObject> arr;
    arr.append(TestObject());
    arr.append(TestObject());

    // Ignore temporary objects created during append
    TestObject::destroyed = 0;
  }

  EXPECT_EQ(TestObject::destroyed, 2);
}

TEST(DynamicArrayDestructorTest, ClearDestroysAllElements) {
  TestObject::destroyed = 0;

  DynamicArray<TestObject> arr;
  arr.append(TestObject());
  arr.append(TestObject());

  TestObject::destroyed = 0;

  arr.clear();

  EXPECT_EQ(TestObject::destroyed, 2);
}

TEST(DynamicArrayDestructorTest, RemoveDestroysAnElement) {
  TestObject::destroyed = 0;

  DynamicArray<TestObject> arr;
  arr.append(TestObject());
  arr.append(TestObject());

  TestObject::destroyed = 0;

  arr.remove(0);

  EXPECT_GE(TestObject::destroyed, 1);
}