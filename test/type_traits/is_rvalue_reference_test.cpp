﻿#include <nek/type_traits/is_rvalue_reference.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_rvalue_reference_test, initialize_true)
{
  STATIC_ASSERT_TRUE(nek::is_rvalue_reference<int&&>);
  STATIC_ASSERT_EQ(nek::is_rvalue_reference<int&&>::type, nek::true_type);
  STATIC_ASSERT_EQ(nek::is_rvalue_reference<int&&>::value_type, bool);
  EXPECT_EQ(true, nek::is_rvalue_reference<int&&>());
  SUCCEED();
}

TEST(is_rvalue_reference_test, initialize_false)
{
  STATIC_ASSERT_FALSE(nek::is_rvalue_reference<int>);
  STATIC_ASSERT_EQ(nek::is_rvalue_reference<int>::type, nek::false_type);
  STATIC_ASSERT_EQ(nek::is_rvalue_reference<int>::value_type, bool);
  EXPECT_EQ(false, nek::is_rvalue_reference<int>());
  SUCCEED();
}

TEST(is_rvalue_reference_test, yes)
{
  using namespace type_traits_test;
  STATIC_ASSERT_TRUE(nek::is_rvalue_reference<int&&>);
  STATIC_ASSERT_TRUE(nek::is_rvalue_reference<int const&&>);
  STATIC_ASSERT_TRUE(nek::is_rvalue_reference<int volatile&&>);
  STATIC_ASSERT_TRUE(nek::is_rvalue_reference<int const volatile&&>);
  STATIC_ASSERT_TRUE(nek::is_rvalue_reference<f1_type&&>);
  STATIC_ASSERT_TRUE(nek::is_rvalue_reference<mf1_type&&>);
  STATIC_ASSERT_TRUE(nek::is_rvalue_reference<int(&&)[]>);
}

TEST(is_rvalue_reference_test, no)
{
  using namespace type_traits_test;
  STATIC_ASSERT_FALSE(nek::is_rvalue_reference<int>);
  STATIC_ASSERT_FALSE(nek::is_rvalue_reference<int*>);
  STATIC_ASSERT_FALSE(nek::is_rvalue_reference<int&>);
  STATIC_ASSERT_FALSE(nek::is_rvalue_reference<int const&>);
  STATIC_ASSERT_FALSE(nek::is_rvalue_reference<f1_type>);
  STATIC_ASSERT_FALSE(nek::is_rvalue_reference<f1_type&>);
  STATIC_ASSERT_FALSE(nek::is_rvalue_reference<mf1_type&>);
  STATIC_ASSERT_FALSE(nek::is_rvalue_reference<int(&)[]>);
}