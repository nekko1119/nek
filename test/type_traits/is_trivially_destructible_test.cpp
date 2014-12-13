#include <nek/type_traits/is_trivially_destructible.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

namespace {
    struct yes {};
    struct no { ~no(){} };
}

TEST(is_trivially_destructible_test, initialize_true)
{
    STATIC_ASSERT_TRUE(nek::is_trivially_destructible<yes>);
    STATIC_ASSERT_EQ(nek::is_trivially_destructible<yes>::type, nek::true_type);
    STATIC_ASSERT_EQ(nek::is_trivially_destructible<yes>::value_type, bool);
    EXPECT_TRUE(nek::is_trivially_destructible<yes>());
}

TEST(is_trivially_destructible_test, initialize_false)
{
    STATIC_ASSERT_FALSE(nek::is_trivially_destructible<no>);
    STATIC_ASSERT_EQ(nek::is_trivially_destructible<no>::type, nek::false_type);
    STATIC_ASSERT_EQ(nek::is_trivially_destructible<no>::value_type, bool);
    EXPECT_FALSE(nek::is_trivially_destructible<no>());
}

TEST(is_trivially_destructible_test, yes)
{
    STATIC_ASSERT_TRUE(nek::is_trivially_destructible<int>);
    STATIC_ASSERT_TRUE(nek::is_trivially_destructible<int const volatile>);
    STATIC_ASSERT_TRUE(nek::is_trivially_destructible<no&>);
    STATIC_ASSERT_TRUE(nek::is_trivially_destructible<no&&>);
    STATIC_ASSERT_TRUE(nek::is_trivially_destructible<no*>);
    STATIC_ASSERT_TRUE(nek::is_trivially_destructible<yes>);
    STATIC_ASSERT_TRUE(nek::is_trivially_destructible<int(*)()>);
    STATIC_ASSERT_TRUE(nek::is_trivially_destructible<int(*)[]>);
}

TEST(is_trivially_destructible_test, no)
{
    STATIC_ASSERT_FALSE(nek::is_trivially_destructible<void>);
    STATIC_ASSERT_FALSE(nek::is_trivially_destructible<no>);
    STATIC_ASSERT_FALSE(nek::is_trivially_destructible<no[1]>);
    STATIC_ASSERT_FALSE(nek::is_trivially_destructible<int()>);
    STATIC_ASSERT_FALSE(nek::is_trivially_destructible<int[]>);
}