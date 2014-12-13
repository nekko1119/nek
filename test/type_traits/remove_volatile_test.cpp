#include <nek/type_traits/remove_volatile.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(remove_volatile_test, normal)
{
    STATIC_ASSERT_EQ(nek::remove_volatile<int>::type, int);
    STATIC_ASSERT_EQ(nek::remove_volatile<int const>::type, int const);
    STATIC_ASSERT_EQ(nek::remove_volatile<int volatile>::type, int);
    STATIC_ASSERT_EQ(nek::remove_volatile<int const volatile>::type, int const);
    STATIC_ASSERT_EQ(nek::remove_volatile<int* volatile>::type, int*);
    STATIC_ASSERT_EQ(nek::remove_volatile<int volatile*>::type, int volatile*);
    STATIC_ASSERT_EQ(nek::remove_volatile<int volatile&>::type, int volatile&);
    STATIC_ASSERT_EQ(nek::remove_volatile<int volatile&&>::type, int volatile&&);
    STATIC_ASSERT_EQ(nek::remove_volatile<int[]>::type, int[]);
    STATIC_ASSERT_EQ(nek::remove_volatile<int volatile[]>::type, int[]);
    STATIC_ASSERT_EQ(nek::remove_volatile<int const volatile[]>::type, int const[]);
    STATIC_ASSERT_EQ(nek::remove_volatile<int[2]>::type, int[2]);
    STATIC_ASSERT_EQ(nek::remove_volatile<int volatile[2]>::type, int[2]);
    STATIC_ASSERT_EQ(nek::remove_volatile<int const volatile[2]>::type, int const[2]);
    STATIC_ASSERT_EQ(nek::remove_volatile<int(*volatile)[]>::type, int(*)[]);
    STATIC_ASSERT_EQ(nek::remove_volatile<int(&)[]>::type, int(&)[]);
    SUCCEED();
}