#include <nek/type_traits/is_array.hpp>
#include <gtest/gtest.h>
#include <array>
#include "static_assert.hpp"

TEST(is_array_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_array<int[]>>();
}

TEST(is_array_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_array<int>>();
}

TEST(is_array_test, yes)
{
    STATIC_ASSERT_TRUE(nek::is_array<int[]>);
    STATIC_ASSERT_TRUE(nek::is_array<int[1]>);
    STATIC_ASSERT_TRUE(nek::is_array<int[][1]>);
    STATIC_ASSERT_TRUE(nek::is_array<int[1][1]>);
    STATIC_ASSERT_TRUE(nek::is_array<int const volatile[]>);
    STATIC_ASSERT_TRUE(nek::is_array<int*[]>);
    STATIC_ASSERT_TRUE(nek::is_array<void(*[])()>);
}

TEST(is_array_test, no)
{
    STATIC_ASSERT_FALSE(nek::is_array<int(*)[]>);
    STATIC_ASSERT_FALSE(nek::is_array<int(&)[]>);
    STATIC_ASSERT_FALSE(nek::is_array<int*>);
    using array_type = std::array<int, 1>;
    STATIC_ASSERT_FALSE(nek::is_array<array_type>);
    STATIC_ASSERT_FALSE(nek::is_array<void(int(&)[1])>);
}
