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
    using dctype = nek::is_default_constructible<int>;
    STATIC_ASSERT_TRUE(dctype);
    STATIC_ASSERT_EQ(dctype::type, nek::true_type);
    STATIC_ASSERT_EQ(dctype::value_type, bool);
    EXPECT_EQ(true, dctype());
}

TEST(is_default_constructible_test, initialize_false)
{
    using dctype = nek::is_default_constructible<non_def>;
    STATIC_ASSERT_FALSE(dctype);
    STATIC_ASSERT_EQ(dctype::type, nek::false_type);
    STATIC_ASSERT_EQ(dctype::value_type, bool);
    EXPECT_EQ(false, dctype());
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
