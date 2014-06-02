#include <nek/type_traits/remove_const.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(remove_const_test, check)
{
  STATIC_ASSERT_EQ(nek::remove_const<int>::type, int);
  STATIC_ASSERT_EQ(nek::remove_const<int const>::type, int);
  STATIC_ASSERT_EQ(nek::remove_const<int volatile>::type, int volatile);
  STATIC_ASSERT_EQ(nek::remove_const<int const volatile>::type, int volatile);
  STATIC_ASSERT_EQ(nek::remove_const<int* const>::type, int*);
  STATIC_ASSERT_EQ(nek::remove_const<int const*>::type, int const*);
  STATIC_ASSERT_EQ(nek::remove_const<int const&>::type, int const&);
  STATIC_ASSERT_EQ(nek::remove_const<int const&&>::type, int const&&);
  STATIC_ASSERT_EQ(nek::remove_const<int[]>::type, int[]);
  STATIC_ASSERT_EQ(nek::remove_const<int const[]>::type, int[]);
  STATIC_ASSERT_EQ(nek::remove_const<int const volatile[]>::type, int volatile[]);
  STATIC_ASSERT_EQ(nek::remove_const<int[2]>::type, int[2]);
  STATIC_ASSERT_EQ(nek::remove_const<int const[2]>::type, int[2]);
  STATIC_ASSERT_EQ(nek::remove_const<int const volatile[2]>::type, int volatile[2]);
  STATIC_ASSERT_EQ(nek::remove_const<int (*const)[]>::type, int (*)[]);
  STATIC_ASSERT_EQ(nek::remove_const<int (&)[]>::type, int (&)[]);
  SUCCEED();
}