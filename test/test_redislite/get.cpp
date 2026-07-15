#include "redislite.h"
#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <iostream>

// Test 1: Get existing key
TEST(RedisLiteGetTest, GetExisting) {
  RedisLite redis;
  redis.processCommand("SET mykey myval");

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("GET mykey"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "myval\n");
}

// Test 2: Get non-existing key
TEST(RedisLiteGetTest, GetNonExisting) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("GET missingkey"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "Error: Key not found\n");
}

// Test 3: Get spaces in key
TEST(RedisLiteGetTest, GetSpacesInKey) {
  RedisLite redis;
  redis.processCommand("SET \"my key\" val");

  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("GET \"my key\""));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "val\n");
}

// Test 4: Get syntax error missing key
TEST(RedisLiteGetTest, GetSyntaxErrorMissingKey) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("GET"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "Error: GET requires a key\n");
}

// Test 5: Get syntax error extra arguments
TEST(RedisLiteGetTest, GetSyntaxErrorExtraArgs) {
  RedisLite redis;
  std::stringstream buffer;
  std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

  EXPECT_TRUE(redis.processCommand("GET key extra"));

  std::cout.rdbuf(oldCout);
  EXPECT_EQ(buffer.str(), "Error: GET requires a key\n");
}
