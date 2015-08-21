#include <nek/type_traits/is_byte.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(is_byte_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_byte<char>>();
}

TEST(is_byte_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_byte<int>>();
}

TEST(is_byte_test, yes)
{
    STATIC_ASSERT_TRUE_VALUE(nek::is_byte<char>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_byte<signed char>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_byte<unsigned char>);
}

TEST(is_byte_test, no)
{
    STATIC_ASSERT_FALSE_VALUE(nek::is_byte<const char>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_byte<char*>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_byte<int>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_byte<wchar_t>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_byte<void>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_byte<char16_t>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_byte<char32_t>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_byte<char[]>);
}
