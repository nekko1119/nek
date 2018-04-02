#include <nek/type_traits/is_signed.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(is_signed_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_signed<int>>();
}

TEST(is_signed_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_signed<unsigned int>>();
}

TEST(is_signed_test, yes)
{
    STATIC_ASSERT_TRUE_VALUE(nek::is_signed<int>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_signed<float>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_signed<long double>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_signed<char>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_signed<signed char>);
}

TEST(is_signed_test, no)
{
    STATIC_ASSERT_FALSE_VALUE(nek::is_signed<unsigned char>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_signed<std::nullptr_t>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_signed<void>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_signed<bool>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_signed<int*>);
}
