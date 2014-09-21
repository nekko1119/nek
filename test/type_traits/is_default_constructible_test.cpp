#include <nek/type_traits/is_default_construdtible.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(is_default_constructible_test, initialize_true)
{
  using type = nek::is_default_constructible<int>;
  STATIC_ASSERT_TRUE(type);
  STATIC_ASSERT_EQ(type, nek::true_type);
  STATIC_ASSERT_EQ(type::value_type, bool);
  EXPECT_EQ(true, type());
}
