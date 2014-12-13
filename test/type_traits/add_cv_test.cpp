#include <nek/type_traits/add_cv.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(add_cv_test, normal)
{
    STATIC_ASSERT_EQ(nek::add_cv<int>::type, int const volatile);
    STATIC_ASSERT_EQ(nek::add_cv<int const>::type, int const volatile);
    STATIC_ASSERT_EQ(nek::add_cv<int volatile>::type, int const volatile);
    STATIC_ASSERT_EQ(nek::add_cv<int const volatile>::type, int const volatile);
    STATIC_ASSERT_EQ(nek::add_cv<int*>::type, int* const volatile);
    STATIC_ASSERT_EQ(nek::add_cv<int volatile*>::type, int volatile* const volatile);
    STATIC_ASSERT_EQ(nek::add_cv<int const*>::type, int const* const volatile);
    STATIC_ASSERT_EQ(nek::add_cv<int&>::type, int&);
    STATIC_ASSERT_EQ(nek::add_cv<int const&>::type, int const&);
    STATIC_ASSERT_EQ(nek::add_cv<int&&>::type, int&&);
    STATIC_ASSERT_EQ(nek::add_cv<int const&&>::type, int const&&);
    STATIC_ASSERT_EQ(nek::add_cv<int[]>::type, int const volatile[]);
    STATIC_ASSERT_EQ(nek::add_cv<int const[]>::type, int const volatile[]);
    STATIC_ASSERT_EQ(nek::add_cv<int(*)[]>::type, int(*const volatile)[]);
    STATIC_ASSERT_EQ(nek::add_cv<int(&)[]>::type, int(&)[]);
    SUCCEED();
}