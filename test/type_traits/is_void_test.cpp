#include <nek/type_traits/is_void.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(is_void_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_void<void>>();
}

TEST(is_void_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_void<int>>();
}

TEST(is_void_test, yes)
{
    STATIC_ASSERT_TRUE_VALUE(nek::is_void<void>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_void<void const>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_void<void volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_void<void const volatile>);
    SUCCEED();
}

TEST(is_void_test, no)
{
    STATIC_ASSERT_FALSE_VALUE(nek::is_void<int>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_void<void*>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_void<void*&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_void<void*&&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_void<void()>);
    SUCCEED();
}