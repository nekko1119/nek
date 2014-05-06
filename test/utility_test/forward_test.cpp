#include <type_traits>
#include <nek/utility/forward.hpp>
#include <gtest/gtest.h>

TEST(forward_test, return_rvalue_reference_if_template_argement_is_value_type)
{
  int x = 0;
  bool b = std::is_same<int&&, decltype(nek::forward<int>(x))>::value;
  EXPECT_TRUE(b);
}

TEST(forward_test, return_rvalue_reference_if_template_argement_is_rvalue_reference_type)
{
  int x = 0;
  bool b = std::is_same<int&&, decltype(nek::forward<int&&>(x))>::value;
  EXPECT_TRUE(b);
}

TEST(forward_test, return_lvalue_reference_if_template_argement_is_lvalue_reference_type)
{
  int x = 0;
  bool b = std::is_same<int&, decltype(nek::forward<int&>(x))>::value;
  EXPECT_TRUE(b);
}