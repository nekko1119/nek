#include <nek/type_traits/is_union.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_union_test, initialize_true)
{
  using namespace type_traits_test;
  STATIC_ASSERT_TRUE(nek::is_union<union_type>);
  STATIC_ASSERT_EQ(nek::is_union<union_type>::type, nek::true_type);
  STATIC_ASSERT_EQ(nek::is_union<union_type>::value_type, bool);
  EXPECT_EQ(true, nek::is_union<union_type>());
  SUCCEED();
}

TEST(is_union_test, initialize_false)
{
  STATIC_ASSERT_FALSE(nek::is_union<int>);
  STATIC_ASSERT_EQ(nek::is_union<int>::type, nek::false_type);
  STATIC_ASSERT_EQ(nek::is_union<int>::value_type, bool);
  EXPECT_EQ(false, nek::is_union<int>());
  SUCCEED();
}

TEST(is_union_test, yes)
{
  using namespace type_traits_test;
  STATIC_ASSERT_TRUE(nek::is_union<union_type>);
  STATIC_ASSERT_TRUE(nek::is_union<union_type const>);
  STATIC_ASSERT_TRUE(nek::is_union<union_type volatile>);
  STATIC_ASSERT_TRUE(nek::is_union<union_type const volatile>);
  SUCCEED();
}

TEST(is_union_test, no)
{
  using namespace type_traits_test;
  STATIC_ASSERT_FALSE(nek::is_union<int>);
  STATIC_ASSERT_FALSE(nek::is_union<void>);
  STATIC_ASSERT_FALSE(nek::is_union<union_type*>);
  STATIC_ASSERT_FALSE(nek::is_union<union_type[]>);
  STATIC_ASSERT_FALSE(nek::is_union<union_type&>);
  STATIC_ASSERT_FALSE(nek::is_union<union_type&&>);
  STATIC_ASSERT_FALSE(nek::is_union<class_type>);
  STATIC_ASSERT_FALSE(nek::is_union<enum_type>);
  STATIC_ASSERT_FALSE(nek::is_union<f1_type>);
  STATIC_ASSERT_FALSE(nek::is_union<mf1_type>);
  SUCCEED();
}