#include <nek/type_traits/is_floating_point.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_floating_point_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_floating_point<float>>();
}

TEST(is_floating_point_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_floating_point<int>>();
}

TEST(is_floating_point_test, yes)
{
    STATIC_ASSERT_TRUE_VALUE(nek::is_floating_point<float>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_floating_point<float const>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_floating_point<float volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_floating_point<float const volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_floating_point<double>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_floating_point<long double>);
    SUCCEED();
}

TEST(is_floating_point_test, no)
{
    using namespace type_traits_test;
    STATIC_ASSERT_FALSE_VALUE(nek::is_floating_point<int>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_floating_point<void>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_floating_point<float*>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_floating_point<float[]>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_floating_point<float&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_floating_point<float&&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_floating_point<class_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_floating_point<f1_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_floating_point<mf1_type>);
    SUCCEED();
}
