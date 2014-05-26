#include <nek/type_traits/add_const.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(add_const_test, check)
{
  STATIC_ASSERT_EQ(nek::add_const<int>::type, int const);
  STATIC_ASSERT_EQ(nek::add_const<int const>::type, int const);
  STATIC_ASSERT_EQ(nek::add_const<int volatile>::type, int const volatile);
  STATIC_ASSERT_EQ(nek::add_const<int*>::type, int* const);
  STATIC_ASSERT_EQ(nek::add_const<int&>::type, int&);
  STATIC_ASSERT_EQ(nek::add_const<int const&>::type, int const&);
  STATIC_ASSERT_EQ(nek::add_const<int&&>::type, int&&);
  STATIC_ASSERT_EQ(nek::add_const<int const&&>::type, int const&&);
  STATIC_ASSERT_EQ(nek::add_const<int []>::type, int const []);
  STATIC_ASSERT_EQ(nek::add_const<int const []>::type, int const []);
  STATIC_ASSERT_EQ(nek::add_const<int (*)[]>::type, int (* const)[]);
  STATIC_ASSERT_EQ(nek::add_const<int (&)[]>::type, int (&)[]);
  SUCCEED();
}