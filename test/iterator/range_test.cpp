#include <nek/iterator/range.hpp>
#include <gtest/gtest.h>
#include <list>

TEST(range_test, array)
{
  int arr[] = {1, 2, 3};
  int const* const first = nek::begin(arr);
  EXPECT_EQ(arr[0], *first);
  EXPECT_EQ(&arr[0], first);
  int const* const last = nek::end(arr);
  EXPECT_EQ(arr[2], *(last - 1));
  EXPECT_EQ(&arr[2], last - 1);
}

TEST(range_test, list)
{
  std::list<int> list = {1, 2, 3};
  auto const first = nek::begin(list);
  EXPECT_EQ(list.front(), *first);
  EXPECT_EQ(list.begin(), first);
  auto last = nek::end(list);
  EXPECT_EQ(list.end(), last);
  --last;
  EXPECT_EQ(list.back(), *last);
}