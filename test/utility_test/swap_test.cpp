#include <nek/utility/swap.hpp>
#include <gtest/gtest.h>
#include <string>

TEST(swap_test, primitive)
{
  int x = 1;
  int y = 2;
  nek::swap(x, y);
  EXPECT_EQ(2, x);
  EXPECT_EQ(1, y);
}

TEST(swap_test, std_string)
{
  std::string str1 = "abc";
  std::string str2 = "def";
  nek::swap(str1, str2);
  EXPECT_EQ("def", str1);
  EXPECT_EQ("abc", str2);
}