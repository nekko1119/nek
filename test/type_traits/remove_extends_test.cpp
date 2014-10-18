#include <nek/type_traits/remove_extends.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(remove_extends_test, normal)
{
	STATIC_ASSERT_EQ(nek::remove_extends<int>::type, int);
	STATIC_ASSERT_EQ(nek::remove_extends<int[]>::type, int);
	STATIC_ASSERT_EQ(nek::remove_extends<int[1]>::type, int);
	STATIC_ASSERT_EQ(nek::remove_extends<int const>::type, int const);
	STATIC_ASSERT_EQ(nek::remove_extends<int volatile>::type, int volatile);
	STATIC_ASSERT_EQ(nek::remove_extends<int const volatile>::type, int const volatile);
	STATIC_ASSERT_EQ(nek::remove_extends<int const[]>::type, int const);
	STATIC_ASSERT_EQ(nek::remove_extends<int volatile[]>::type, int volatile);
	STATIC_ASSERT_EQ(nek::remove_extends<int const volatile[]>::type, int const volatile);
	STATIC_ASSERT_EQ(nek::remove_extends<int[][1]>::type, int[1]);
	STATIC_ASSERT_EQ(nek::remove_extends<int[1][1]>::type, int[1]);
	STATIC_ASSERT_EQ(nek::remove_extends<int(*)[]>::type, int(*)[]);
	STATIC_ASSERT_EQ(nek::remove_extends<int(&)[]>::type, int(&)[]);
	STATIC_ASSERT_EQ(nek::remove_extends<int(*[])()>::type, int(*)());
	STATIC_ASSERT_EQ(nek::remove_extends<int*[]>::type, int*);
	STATIC_ASSERT_EQ(nek::remove_extends<int const* const[]>::type, int const* const);
}