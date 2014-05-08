#include <nek/utility/swap.hpp>
#include <gtest/gtest.h>

TEST(swap_test, primitive)
{
  int x = 42;
  int y = 91;
  nek::swap(x, y);
  EXPECT_EQ(91, x);
  EXPECT_EQ(42, y);
}