#include <nek/type_traits/has_iterator.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

#define NEK_MEMBER_TYPE iterator

#include "has_member_type.hpp"

#undef NEK_MEMBER_TYPE

TEST(has_iterator_test, initialize_true)
{
  STATIC_ASSERT_TRUE(nek::has_iterator<has_member_type>);
  STATIC_ASSERT_EQ(nek::has_iterator<has_member_type>::type, nek::true_type);
  STATIC_ASSERT_EQ(nek::has_iterator<has_member_type>::value_type, bool);
  EXPECT_EQ(true, nek::has_iterator<has_member_type>());
  SUCCEED();
}

TEST(has_iterator_test, initialize_false)
{
  STATIC_ASSERT_FALSE(nek::has_iterator<int>);
  STATIC_ASSERT_EQ(nek::has_iterator<int>::type, nek::false_type);
  STATIC_ASSERT_EQ(nek::has_iterator<int>::value_type, bool);
  EXPECT_EQ(false, nek::has_iterator<int>());
  SUCCEED();
}

TEST(has_iterator_test, check)
{
  NEK_HAS_MEMBER_TYPE(nek::has_iterator);
  SUCCEED();
}