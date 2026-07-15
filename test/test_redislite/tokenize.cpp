#include "redislite.h"
#include <gtest/gtest.h>
#include <string>

// Test 1: Basic space-separated tokenization
TEST(RedisLiteTokenizeTest, TokenizeBasic) {
  RedisLite redis;
  DynamicArray<std::string> tokens = redis.tokenize("SET key value");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens.get(0), "SET");
  EXPECT_EQ(tokens.get(1), "key");
  EXPECT_EQ(tokens.get(2), "value");
}

// Test 2: Double quotes with spaces
TEST(RedisLiteTokenizeTest, TokenizeDoubleQuotes) {
  RedisLite redis;
  DynamicArray<std::string> tokens = redis.tokenize("SET key \"hello world\"");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens.get(0), "SET");
  EXPECT_EQ(tokens.get(1), "key");
  EXPECT_EQ(tokens.get(2), "hello world");
}

// Test 3: Single quotes with spaces
TEST(RedisLiteTokenizeTest, TokenizeSingleQuotes) {
  RedisLite redis;
  DynamicArray<std::string> tokens = redis.tokenize("SET key 'single quote space'");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens.get(0), "SET");
  EXPECT_EQ(tokens.get(1), "key");
  EXPECT_EQ(tokens.get(2), "single quote space");
}

// Test 4: Escaped quotes inside quoted strings
TEST(RedisLiteTokenizeTest, TokenizeEscapedQuotes) {
  RedisLite redis;
  DynamicArray<std::string> tokens = redis.tokenize("SET key \"hello \\\"world\\\"\"");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens.get(0), "SET");
  EXPECT_EQ(tokens.get(1), "key");
  EXPECT_EQ(tokens.get(2), "hello \"world\"");
}

// Test 5: Graceful fallback for unclosed quotes
TEST(RedisLiteTokenizeTest, TokenizeUnclosedQuotes) {
  RedisLite redis;
  DynamicArray<std::string> tokens = redis.tokenize("SET key \"unclosed quote space");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens.get(0), "SET");
  EXPECT_EQ(tokens.get(1), "key");
  EXPECT_EQ(tokens.get(2), "unclosed quote space");
}

// Test 6: Extra spaces tokenization
TEST(RedisLiteTokenizeTest, TokenizeMultipleSpaces) {
  RedisLite redis;
  DynamicArray<std::string> tokens = redis.tokenize("  SET   key   value  ");
  EXPECT_EQ(tokens.size(), 3);
  EXPECT_EQ(tokens.get(0), "SET");
  EXPECT_EQ(tokens.get(1), "key");
  EXPECT_EQ(tokens.get(2), "value");
}
