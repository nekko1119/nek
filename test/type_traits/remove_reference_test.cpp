#include <nek/type_traits/remove_reference.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(remove_reference_test, check)
{
  STATIC_ASSERT_EQ(nek::remove_reference<int>::type, int);
  STATIC_ASSERT_EQ(nek::remove_reference<int const>::type, int const);
  STATIC_ASSERT_EQ(nek::remove_reference<int volatile>::type, int volatile);
  STATIC_ASSERT_EQ(nek::remove_reference<int*>::type, int*);
  STATIC_ASSERT_EQ(nek::remove_reference<int&>::type, int);
  STATIC_ASSERT_EQ(nek::remove_reference<int const&>::type, int const);
  STATIC_ASSERT_EQ(nek::remove_reference<int&&>::type, int);
  STATIC_ASSERT_EQ(nek::remove_reference<int const&&>::type, int const);
  STATIC_ASSERT_EQ(nek::remove_reference<int []>::type, int []);
  STATIC_ASSERT_EQ(nek::remove_reference<int (&)[]>::type, int []);
  STATIC_ASSERT_EQ(nek::remove_reference<int (&)()>::type, int ());
  STATIC_ASSERT_EQ(nek::remove_reference<int*&>::type, int*);
  SUCCEED();
}