#include <nek/type_traits/remove_cv.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(remove_cv_test, normal)
{
	STATIC_ASSERT_EQ(nek::remove_cv<int>::type, int);
	STATIC_ASSERT_EQ(nek::remove_cv<int const>::type, int);
	STATIC_ASSERT_EQ(nek::remove_cv<int volatile>::type, int);
	STATIC_ASSERT_EQ(nek::remove_cv<int const volatile>::type, int);
	STATIC_ASSERT_EQ(nek::remove_cv<int const*>::type, int const*);
	STATIC_ASSERT_EQ(nek::remove_cv<int volatile*>::type, int volatile*);
	STATIC_ASSERT_EQ(nek::remove_cv<int const volatile*>::type, int const volatile*);
	STATIC_ASSERT_EQ(nek::remove_cv<int&>::type, int&);
	STATIC_ASSERT_EQ(nek::remove_cv<int const&>::type, int const&);
	STATIC_ASSERT_EQ(nek::remove_cv<int&&>::type, int&&);
	STATIC_ASSERT_EQ(nek::remove_cv<int const&&>::type, int const&&);
	STATIC_ASSERT_EQ(nek::remove_cv<int[]>::type, int[]);
	STATIC_ASSERT_EQ(nek::remove_cv<int const volatile[]>::type, int[]);
	STATIC_ASSERT_EQ(nek::remove_cv<int(*const volatile)[]>::type, int(*)[]);
	STATIC_ASSERT_EQ(nek::remove_cv<int(&)[]>::type, int(&)[]);
	SUCCEED();
}