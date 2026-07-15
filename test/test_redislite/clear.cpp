#include "redislite.h"
#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <iostream>

// Test 1: Clear empty
TEST(RedisLiteClearTest, ClearEmpty) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("CLEAR"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "OK\n");

  std::stringstream bufferCount;
  std::streambuf* oldCoutCount = std::cout.rdbuf(bufferCount.rdbuf());
  redis.processCommand("COUNT");
  std::cout.rdbuf(oldCoutCount);
  EXPECT_EQ(bufferCount.str(), "0\n");
}

// Test 2: Clear non-empty
TEST(RedisLiteClearTest, ClearNonEmpty) {
  RedisLite redis;
  redis.processCommand("SET k1 v1");
  redis.processCommand("SET k2 v2");

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("CLEAR"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "OK\n");

  std::string val;
  EXPECT_FALSE(redis.get("k1", val));
}

// Test 3: Clear multiple times
TEST(RedisLiteClearTest, ClearMultiple) {
  RedisLite redis;
  redis.processCommand("SET k1 v1");

  redis.processCommand("CLEAR");
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("CLEAR"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "OK\n");
}

// Test 4: Clear syntax error extra arguments
TEST(RedisLiteClearTest, ClearSyntaxErrorExtraArgs) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("CLEAR extra"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "Error: CLEAR does not take any arguments\n");
}

// Test 5: Clear and insert again
TEST(RedisLiteClearTest, ClearAndInsert) {
  RedisLite redis;
  redis.processCommand("SET k1 v1");
  redis.processCommand("CLEAR");
  redis.processCommand("SET k2 v2");

  std::string val;
  EXPECT_FALSE(redis.get("k1", val));
  EXPECT_TRUE(redis.get("k2", val));
  EXPECT_EQ(val, "v2");
}
