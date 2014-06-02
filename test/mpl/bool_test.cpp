﻿#include <nek/mpl/bool.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"

using nek::mpl::bool_;

TEST(bool_test, member)
{
  using true_t = bool_<true>;
  STATIC_ASSERT_EQ(typename true_t::value_type, bool);
  STATIC_ASSERT_EQ(typename true_t::type, true_t);
  STATIC_ASSERT_EQ(typename true_t::tag, nek::mpl::integral_c_tag);
  EXPECT_EQ(true, true_t::value);
  EXPECT_EQ(true, true_t());

  using false_t = bool_<false>;
  STATIC_ASSERT_EQ(typename false_t::value_type, bool);
  STATIC_ASSERT_EQ(typename false_t::type, false_t);
  STATIC_ASSERT_EQ(typename false_t::tag, nek::mpl::integral_c_tag);
  EXPECT_EQ(false, false_t::value);
  EXPECT_EQ(false, false_t());

  SUCCEED();
}