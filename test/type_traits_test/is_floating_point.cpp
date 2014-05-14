#include <nek/type_traits/is_floating_point.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_floating_point_test, initialize_true)
{
  using namespace type_traits_test;
  STATIC_ASSERT_TRUE(nek::is_floating_point<float>);
  STATIC_ASSERT_EQ(nek::is_floating_point<float>::type, nek::true_type);
  STATIC_ASSERT_EQ(nek::is_floating_point<float>::value_type, bool);
  EXPECT_EQ(true, nek::is_floating_point<float>());
  SUCCEED();
}

TEST(is_floating_point_test, initialize_false)
{
  STATIC_ASSERT_FALSE(nek::is_floating_point<int>);
  STATIC_ASSERT_EQ(nek::is_floating_point<int>::type, nek::false_type);
  STATIC_ASSERT_EQ(nek::is_floating_point<int>::value_type, bool);
  EXPECT_EQ(false, nek::is_floating_point<int>());
  SUCCEED();
}

TEST(is_floating_point_test, yes)
{
  using namespace type_traits_test;
  STATIC_ASSERT_TRUE(nek::is_floating_point<float>);
  STATIC_ASSERT_TRUE(nek::is_floating_point<float const>);
  STATIC_ASSERT_TRUE(nek::is_floating_point<float volatile>);
  STATIC_ASSERT_TRUE(nek::is_floating_point<float const volatile>);
  STATIC_ASSERT_TRUE(nek::is_floating_point<double>);
  STATIC_ASSERT_TRUE(nek::is_floating_point<long double>);
  SUCCEED();
}

TEST(is_floating_point_test, no)
{
  using namespace type_traits_test;
  STATIC_ASSERT_FALSE(nek::is_floating_point<int>);
  STATIC_ASSERT_FALSE(nek::is_floating_point<void>);
  STATIC_ASSERT_FALSE(nek::is_floating_point<float*>);
  STATIC_ASSERT_FALSE(nek::is_floating_point<float[]>);
  STATIC_ASSERT_FALSE(nek::is_floating_point<float&>);
  STATIC_ASSERT_FALSE(nek::is_floating_point<float&&>);
  STATIC_ASSERT_FALSE(nek::is_floating_point<class_type>);
  STATIC_ASSERT_FALSE(nek::is_floating_point<f1_type>);
  STATIC_ASSERT_FALSE(nek::is_floating_point<mf1_type>);
  SUCCEED();
}