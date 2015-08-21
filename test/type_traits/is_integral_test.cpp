#include <nek/type_traits/is_integral.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_integral_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_integral<int>>();
}

TEST(is_integral_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_integral<double>>();
}

TEST(is_integral_test, yes)
{
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<bool>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<char>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<signed char>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<unsigned char>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<wchar_t>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<short>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<unsigned short>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<int>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<unsigned int>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<long>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<unsigned long>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<long long>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<unsigned long long>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<int const>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<int volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_integral<int const volatile>);
    SUCCEED();
}

TEST(is_integral_test, no)
{
    using namespace type_traits_test;
    STATIC_ASSERT_FALSE_VALUE(nek::is_integral<float>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_integral<void>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_integral<int*>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_integral<int[]>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_integral<int&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_integral<int&&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_integral<class_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_integral<f1_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_integral<mf1_type>);
    SUCCEED();
}