#include <nek/iterator/distance.hpp>
#include <gtest/gtest.h>
#include <forward_list>
#include <list>
#include <vector>

TEST(distance_test, random_access)
{
  std::vector<int> v = {1, 2, 3};
  auto const actual = nek::distance(v.begin(), v.end());
  EXPECT_EQ(3, actual);
}

TEST(distance_test, bidirectional)
{
  std::list<int> l = {1, 2, 3};
  auto const actual = nek::distance(l.begin(), l.end());
  EXPECT_EQ(3, actual);
}

TEST(distance_test, forward)
{
  std::forward_list<int> l = {1, 2, 3};
  auto const actual = nek::distance(l.begin(), l.end());
  EXPECT_EQ(3, actual);
}