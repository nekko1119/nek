#include <nek/type_traits/add_volatile.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(add_volatile_test, normal)
{
    STATIC_ASSERT_EQ(nek::add_volatile<int>::type, int volatile);
    STATIC_ASSERT_EQ(nek::add_volatile<int volatile>::type, int volatile);
    STATIC_ASSERT_EQ(nek::add_volatile<int const>::type, int const volatile);
    STATIC_ASSERT_EQ(nek::add_volatile<int*>::type, int* volatile);
    STATIC_ASSERT_EQ(nek::add_volatile<int&>::type, int&);
    STATIC_ASSERT_EQ(nek::add_volatile<int volatile&>::type, int volatile&);
    STATIC_ASSERT_EQ(nek::add_volatile<int&&>::type, int&&);
    STATIC_ASSERT_EQ(nek::add_volatile<int volatile&&>::type, int volatile&&);
    STATIC_ASSERT_EQ(nek::add_volatile<int[]>::type, int volatile[]);
    STATIC_ASSERT_EQ(nek::add_volatile<int volatile[]>::type, int volatile[]);
    STATIC_ASSERT_EQ(nek::add_volatile<int(*)[]>::type, int(*volatile)[]);
    STATIC_ASSERT_EQ(nek::add_volatile<int(&)[]>::type, int(&)[]);
    SUCCEED();
}