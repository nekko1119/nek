#include <nek/type_traits/is_constructible.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

namespace
{
  struct x
  {
    explicit x(int){}
    x(x const&) = delete;
  };
}

TEST(is_constructible_test, yes)
{
  using xi_type = nek::is_constructible<x, int>;
  STATIC_ASSERT_TRUE(xi_type);
}

TEST(is_constructible_test, no)
{
  using xx_type = nek::is_constructible<x, x>;
  using fii_type = nek::is_constructible<void (int, int), int, int>;
  using vi_type = nek::is_constructible<void, int>;
  STATIC_ASSERT_FALSE(xx_type);
  STATIC_ASSERT_FALSE(fii_type);
  STATIC_ASSERT_FALSE(vi_type);
}
