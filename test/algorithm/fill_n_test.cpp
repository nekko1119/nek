#include <nek/algorithm/fill_n.hpp>
#include <gtest/gtest.h>

TEST(fill_n_test, array)
{
  int a[] = {0, 0, 0, 0, 0};
  nek::fill_n(a + 1, 3, 10);
  EXPECT_EQ(0, a[0]);
  EXPECT_EQ(10, a[1]);
  EXPECT_EQ(10, a[2]);
  EXPECT_EQ(10, a[3]);
  EXPECT_EQ(0, a[4]);
}