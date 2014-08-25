#include <nek/container/function/front.hpp>
#include <gtest/gtest.h>
#include <list>

TEST(front_test, list)
{
  std::list<int> const l = {1, 2, 3};
  EXPECT_EQ(1, nek::front(l));
}

TEST(front_test, array)
{
  constexpr int a[] = {1, 2, 3};
  // CTP 2013's constexpr is very poor.
  //static_assert(1 == nek::front(a), "");
  EXPECT_EQ(1, nek::front(a));
}
