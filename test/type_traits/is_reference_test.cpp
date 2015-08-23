#include <nek/type_traits/is_reference.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_reference_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_reference<int&>>();
}

TEST(is_reference_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_reference<int>>();
}

TEST(is_reference_test, yes)
{
    using namespace type_traits_test;
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<int&>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<int const&>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<int volatile&>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<int const volatile&>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<f1_type&>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<mf1_type&>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<int(&)[]>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<int(*&)[]>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<int&&>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<int const&&>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<int volatile&&>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<int const volatile&&>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<f1_type&&>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<mf1_type&&>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<int(&&)[]>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_reference<int(*&&)[]>);
}

TEST(is_reference_test, no)
{
    using namespace type_traits_test;
    STATIC_ASSERT_FALSE_VALUE(nek::is_reference<int>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_reference<int*>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_reference<f1_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_reference<mf1_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_reference<int(*)[]>);
}
