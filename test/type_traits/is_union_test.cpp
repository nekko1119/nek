#include <nek/type_traits/is_union.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_union_test, initialize_true)
{
    using namespace type_traits_test;
    nektest::require_true_type_member<nek::is_union<union_type>>();
}

TEST(is_union_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_union<int>>();
}

TEST(is_union_test, yes)
{
    using namespace type_traits_test;
    STATIC_ASSERT_TRUE_VALUE(nek::is_union<union_type>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_union<union_type const>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_union<union_type volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_union<union_type const volatile>);
    SUCCEED();
}

TEST(is_union_test, no)
{
    using namespace type_traits_test;
    STATIC_ASSERT_FALSE_VALUE(nek::is_union<int>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_union<void>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_union<union_type*>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_union<union_type[]>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_union<union_type&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_union<union_type&&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_union<class_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_union<enum_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_union<f1_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_union<mf1_type>);
    SUCCEED();
}
