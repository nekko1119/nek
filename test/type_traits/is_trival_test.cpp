#include <nek/type_traits/is_trivial.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

namespace
{
    struct trivial_type
    {
    };

    struct non_trivial_type
    {
        non_trivial_type(){}
    };
}

TEST(is_trival_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_trivial<int>>();
}

TEST(is_trival_test, initialize_false)
{
    using namespace type_traits_test;
    nektest::require_false_type_member<nek::is_trivial<standard_layout_type>>();
}

TEST(is_trivial_test, yes)
{
    using namespace type_traits_test;
    STATIC_ASSERT_TRUE(nek::is_trivial<int>);
    STATIC_ASSERT_TRUE(nek::is_trivial<trivial_type>);
    STATIC_ASSERT_TRUE(nek::is_trivial<int*>);
    STATIC_ASSERT_TRUE(nek::is_trivial<int[]>);
    STATIC_ASSERT_TRUE(nek::is_trivial<enum_type>);
    STATIC_ASSERT_TRUE(nek::is_trivial<union_type>);
    STATIC_ASSERT_TRUE(nek::is_trivial<f1_type>);
    STATIC_ASSERT_TRUE(nek::is_trivial<mf1_type>);
}

TEST(is_trivial_test, no)
{
    STATIC_ASSERT_FALSE(nek::is_trivial<int&>);
    STATIC_ASSERT_FALSE(nek::is_trivial<non_trivial_type>);
    STATIC_ASSERT_FALSE(nek::is_trivial<void>);
    STATIC_ASSERT_FALSE(nek::is_trivial<int()>);
    STATIC_ASSERT_FALSE(nek::is_trivial<int&&>);
}
