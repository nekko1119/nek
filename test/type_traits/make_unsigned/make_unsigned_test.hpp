#ifndef NEK_TYPE_TRAITS_MAKE_UNSIGNED_TEST_HPP
#define NEK_TYPE_TRAITS_MAKE_UNSIGNED_TEST_HPP

#include <nek/type_traits/make_unsigned.hpp>
#include <gtest/gtest.h>
#include <tuple>
#include <type_traits>
#include "../static_assert.hpp"

template <class T>
class make_unsigned_test
  : public ::testing::Test
{
};

TYPED_TEST_CASE_P(make_unsigned_test);

TYPED_TEST_P(make_unsigned_test, type)
{
  using type = typename std::tuple_element<0, TypeParam>::type;
  using expected = typename std::tuple_element<1, TypeParam>::type;
  using actual = typename nek::make_unsigned<type>::type;
  STATIC_ASSERT_EQ(actual, expected);
}

TYPED_TEST_P(make_unsigned_test, const_type)
{
  using type = std::add_const_t<typename std::tuple_element<0, TypeParam>::type>;
  using expected = std::add_const_t<typename std::tuple_element<1, TypeParam>::type>;
  using actual = typename nek::make_unsigned<type>::type;
  STATIC_ASSERT_EQ(actual, expected);
}

REGISTER_TYPED_TEST_CASE_P(make_unsigned_test, type, const_type);

#endif