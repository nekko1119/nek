#include <nek/type_traits/is_volatile.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_volatile_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_volatile<int volatile>>();
}

TEST(is_volatile_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_volatile<int>>();
}

TEST(is_volatile_test, yes)
{
    using namespace type_traits_test;
    STATIC_ASSERT_TRUE_VALUE(nek::is_volatile<int volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_volatile<class_type volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_volatile<enum_type volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_volatile<union_type volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_volatile<void volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_volatile<void(*volatile)()>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_volatile<int* volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_volatile<int volatile[]>);
    SUCCEED();
}

TEST(is_volatile_test, no)
{
    using namespace type_traits_test;
    STATIC_ASSERT_FALSE_VALUE(nek::is_volatile<int>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_volatile<class_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_volatile<enum_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_volatile<union_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_volatile<void>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_volatile<int[]>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_volatile<void(*)()>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_volatile<int volatile*>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_volatile<int volatile&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_volatile<int volatile&&>);
    SUCCEED();
}
