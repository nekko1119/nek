#include <nek/type_traits/is_const.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_const_test, initialize_true)
{
  STATIC_ASSERT_TRUE(nek::is_const<int const>);
  STATIC_ASSERT_EQ(nek::is_const<int const>::type, nek::true_type);
  STATIC_ASSERT_EQ(nek::is_const<int const>::value_type, bool);
  EXPECT_EQ(true, nek::is_const<int const>());
  SUCCEED();
}

TEST(is_const_test, initialize_false)
{
  STATIC_ASSERT_FALSE(nek::is_const<int>);
  STATIC_ASSERT_EQ(nek::is_const<int>::type, nek::false_type);
  STATIC_ASSERT_EQ(nek::is_const<int>::value_type, bool);
  EXPECT_EQ(false, nek::is_const<int>());
  SUCCEED();
}

TEST(is_const_test, yes)
{
  using namespace type_traits_test;
  STATIC_ASSERT_TRUE(nek::is_const<int const>);
  STATIC_ASSERT_TRUE(nek::is_const<class_type const>);
  STATIC_ASSERT_TRUE(nek::is_const<enum_type const>);
  STATIC_ASSERT_TRUE(nek::is_const<union_type const>);
  STATIC_ASSERT_TRUE(nek::is_const<void const>);
  STATIC_ASSERT_TRUE(nek::is_const<void (*const)()>);
  STATIC_ASSERT_TRUE(nek::is_const<int* const>);
  STATIC_ASSERT_TRUE(nek::is_const<int const[]>);
  SUCCEED();
}

TEST(is_const_test, no)
{
  using namespace type_traits_test;
  STATIC_ASSERT_FALSE(nek::is_const<int>);
  STATIC_ASSERT_FALSE(nek::is_const<class_type>);
  STATIC_ASSERT_FALSE(nek::is_const<enum_type>);
  STATIC_ASSERT_FALSE(nek::is_const<union_type>);
  STATIC_ASSERT_FALSE(nek::is_const<void>);
  STATIC_ASSERT_FALSE(nek::is_const<int []>);
  STATIC_ASSERT_FALSE(nek::is_const<void (*)()>);
  STATIC_ASSERT_FALSE(nek::is_const<int const*>);
  STATIC_ASSERT_FALSE(nek::is_const<int const&>);
  STATIC_ASSERT_FALSE(nek::is_const<int const&&>);
  SUCCEED();
}