#include <nek/type_traits/is_const.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_const_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_const<int const>>();
}

TEST(is_const_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_const<int>>();
}

TEST(is_const_test, yes)
{
    using namespace type_traits_test;
    STATIC_ASSERT_TRUE_VALUE(nek::is_const<int const>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_const<class_type const>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_const<enum_type const>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_const<union_type const>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_const<void const>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_const<void(*const)()>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_const<int* const>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_const<int const[]>);
    SUCCEED();
}

TEST(is_const_test, no)
{
    using namespace type_traits_test;
    STATIC_ASSERT_FALSE_VALUE(nek::is_const<int>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_const<class_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_const<enum_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_const<union_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_const<void>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_const<int[]>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_const<void(*)()>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_const<int const*>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_const<int const&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_const<int const&&>);
    SUCCEED();
}