#include <nek/type_traits/propagate_cv.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(propagate_cv_test, normal)
{
    using no_to_no = nek::propagate_cv<int, char>::type;
    using no_to_c = nek::propagate_cv<int, char const>::type;
    using no_to_v = nek::propagate_cv<int, char volatile>::type;
    using no_to_cv = nek::propagate_cv<int, char const volatile>::type;
    using c_to_no = nek::propagate_cv<int const, char>::type;
    using c_to_c = nek::propagate_cv<int const, char const>::type;
    using c_to_v = nek::propagate_cv<int const, char volatile>::type;
    using c_to_cv = nek::propagate_cv<int const, char const volatile>::type;
    using v_to_no = nek::propagate_cv<int volatile, char>::type;
    using v_to_c = nek::propagate_cv<int volatile, char const>::type;
    using v_to_v = nek::propagate_cv<int volatile, char volatile>::type;
    using v_to_cv = nek::propagate_cv<int volatile, char const volatile>::type;
    using cv_to_no = nek::propagate_cv<int const volatile, char>::type;
    using cv_to_c = nek::propagate_cv<int const volatile, char const>::type;
    using cv_to_v = nek::propagate_cv<int const volatile, char volatile>::type;
    using cv_to_cv = nek::propagate_cv<int const volatile, char const volatile>::type;
    STATIC_ASSERT_EQ(no_to_no, char);
    STATIC_ASSERT_EQ(no_to_c, char const);
    STATIC_ASSERT_EQ(no_to_v, char volatile);
    STATIC_ASSERT_EQ(no_to_cv, char const volatile);
    STATIC_ASSERT_EQ(c_to_no, char const);
    STATIC_ASSERT_EQ(c_to_c, char const);
    STATIC_ASSERT_EQ(c_to_v, char const volatile);
    STATIC_ASSERT_EQ(c_to_cv, char const volatile);
    STATIC_ASSERT_EQ(v_to_no, char volatile);
    STATIC_ASSERT_EQ(v_to_c, char const volatile);
    STATIC_ASSERT_EQ(v_to_v, char volatile);
    STATIC_ASSERT_EQ(v_to_cv, char const volatile);
    STATIC_ASSERT_EQ(cv_to_no, char const volatile);
    STATIC_ASSERT_EQ(cv_to_c, char const volatile);
    STATIC_ASSERT_EQ(cv_to_v, char const volatile);
    STATIC_ASSERT_EQ(cv_to_cv, char const volatile);
}
