#include <algorithm>
#include <string>
#include <nek/utility/swap.hpp>
#include <gtest/gtest.h>

TEST(swap_test, primitive)
{
  // setup
  int const expect1 = 1;
  int actual1 = expect1;
  int const expect2 = 2;
  int actual2 = expect2;

  // exercise
  nek::swap(actual1, actual2);

  // verify
  EXPECT_EQ(expect1, actual2);
  EXPECT_EQ(expect2, actual1);
}

TEST(swap_test, std_string)
{
  // setup
  std::string const expect1 = "abc";
  std::string actual1 = expect1;
  std::string const expect2 = "def";
  std::string actual2 = expect2;

  // exercise
  nek::swap(actual1, actual2);

  // verify
  EXPECT_EQ(expect1, actual2);
  EXPECT_EQ(expect2, actual1);
}

TEST(swap_test, array_of_int)
{
  // setup
  int const expect1[] = {1, 2, 3};
  int actual1[3];
  std::copy(std::begin(expect1), std::end(expect1), std::begin(actual1));
  int const expect2[] = {10, 20, 30};
  int actual2[3];
  std::copy(std::begin(expect2), std::end(expect2), std::begin(actual2));

  // exersice
  nek::swap(actual1, actual2);

  // verify
  EXPECT_TRUE(std::equal(std::begin(expect1), std::end(expect1), std::begin(actual2)));
  EXPECT_TRUE(std::equal(std::begin(expect2), std::end(expect2), std::begin(actual1)));
}
