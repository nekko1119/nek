#include <nek/type_traits/is_void.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(is_void_test, initialize_true)
{
	STATIC_ASSERT_TRUE(nek::is_void<void>);
	STATIC_ASSERT_EQ(nek::is_void<void>::type, nek::true_type);
	STATIC_ASSERT_EQ(nek::is_void<void>::value_type, bool);
	EXPECT_EQ(true, nek::is_void<void>());
	SUCCEED();
}

TEST(is_void_test, initialize_false)
{
	STATIC_ASSERT_FALSE(nek::is_void<int>);
	STATIC_ASSERT_EQ(nek::is_void<int>::type, nek::false_type);
	STATIC_ASSERT_EQ(nek::is_void<int>::value_type, bool);
	EXPECT_EQ(false, nek::is_void<int>());
	SUCCEED();
}

TEST(is_void_test, yes)
{
	STATIC_ASSERT_TRUE(nek::is_void<void>);
	STATIC_ASSERT_TRUE(nek::is_void<void const>);
	STATIC_ASSERT_TRUE(nek::is_void<void volatile>);
	STATIC_ASSERT_TRUE(nek::is_void<void const volatile>);
	SUCCEED();
}

TEST(is_void_test, no)
{
	STATIC_ASSERT_FALSE(nek::is_void<int>);
	STATIC_ASSERT_FALSE(nek::is_void<void*>);
	STATIC_ASSERT_FALSE(nek::is_void<void*&>);
	STATIC_ASSERT_FALSE(nek::is_void<void*&&>);
	STATIC_ASSERT_FALSE(nek::is_void<void()>);
	SUCCEED();
}