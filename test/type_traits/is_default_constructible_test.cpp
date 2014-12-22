#include <nek/type_traits/is_default_construdtible.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

namespace
{
    struct can_def
    {
    };

    struct non_def
    {
        non_def(int);
    };
}

TEST(is_default_constructible_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_default_constructible<int>>();
}

TEST(is_default_constructible_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_default_constructible<non_def>>();
}

TEST(is_default_constructible_test, yes)
{
    STATIC_ASSERT_TRUE(nek::is_default_constructible<int>);
    STATIC_ASSERT_TRUE(nek::is_default_constructible<int const volatile>);
    STATIC_ASSERT_TRUE(nek::is_default_constructible<std::nullptr_t>);
    STATIC_ASSERT_TRUE(nek::is_default_constructible<int*>);
    STATIC_ASSERT_TRUE(nek::is_default_constructible<void*>);
    STATIC_ASSERT_TRUE(nek::is_default_constructible<int(*)[]>);
    STATIC_ASSERT_TRUE(nek::is_default_constructible<int[1]>);
    STATIC_ASSERT_TRUE(nek::is_default_constructible<int(*)()>);
    STATIC_ASSERT_TRUE(nek::is_default_constructible<can_def>);
}

TEST(is_default_constructible_test, no)
{
    STATIC_ASSERT_FALSE(nek::is_default_constructible<int&>);
    STATIC_ASSERT_FALSE(nek::is_default_constructible<int&&>);
    STATIC_ASSERT_FALSE(nek::is_default_constructible<int[]>);
    STATIC_ASSERT_FALSE(nek::is_default_constructible<int()>);
    STATIC_ASSERT_FALSE(nek::is_default_constructible<void>);
    STATIC_ASSERT_FALSE(nek::is_default_constructible<non_def>);
}
