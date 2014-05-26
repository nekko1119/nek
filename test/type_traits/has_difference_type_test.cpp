#include <nek/type_traits/has_difference_type.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

#define NEK_MEMBER_TYPE difference_type

#include "has_member_type.hpp"

#undef NEK_MEMBER_TYPE

TEST(has_difference_type_test, initialize_true)
{
  STATIC_ASSERT_TRUE(nek::has_difference_type<has_member_type>);
  STATIC_ASSERT_EQ(nek::has_difference_type<has_member_type>::type, nek::true_type);
  STATIC_ASSERT_EQ(nek::has_difference_type<has_member_type>::value_type, bool);
  EXPECT_EQ(true, nek::has_difference_type<has_member_type>());
  SUCCEED();
}

TEST(has_difference_type_test, initialize_false)
{
  STATIC_ASSERT_FALSE(nek::has_difference_type<int>);
  STATIC_ASSERT_EQ(nek::has_difference_type<int>::type, nek::false_type);
  STATIC_ASSERT_EQ(nek::has_difference_type<int>::value_type, bool);
  EXPECT_EQ(false, nek::has_difference_type<int>());
  SUCCEED();
}

TEST(has_difference_type_test, check)
{
  NEK_HAS_MEMBER_TYPE(nek::has_difference_type);
  SUCCEED();
}