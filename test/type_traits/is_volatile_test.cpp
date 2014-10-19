#include <nek/type_traits/is_volatile.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_volatile_test, initialize_true)
{
	STATIC_ASSERT_TRUE(nek::is_volatile<int volatile>);
	STATIC_ASSERT_EQ(nek::is_volatile<int volatile>::type, nek::true_type);
	STATIC_ASSERT_EQ(nek::is_volatile<int volatile>::value_type, bool);
	EXPECT_EQ(true, nek::is_volatile<int volatile>());
	SUCCEED();
}

TEST(is_volatile_test, initialize_false)
{
	STATIC_ASSERT_FALSE(nek::is_volatile<int>);
	STATIC_ASSERT_EQ(nek::is_volatile<int>::type, nek::false_type);
	STATIC_ASSERT_EQ(nek::is_volatile<int>::value_type, bool);
	EXPECT_EQ(false, nek::is_volatile<int>());
	SUCCEED();
}

TEST(is_volatile_test, yes)
{
	using namespace type_traits_test;
	STATIC_ASSERT_TRUE(nek::is_volatile<int volatile>);
	STATIC_ASSERT_TRUE(nek::is_volatile<class_type volatile>);
	STATIC_ASSERT_TRUE(nek::is_volatile<enum_type volatile>);
	STATIC_ASSERT_TRUE(nek::is_volatile<union_type volatile>);
	STATIC_ASSERT_TRUE(nek::is_volatile<void volatile>);
	STATIC_ASSERT_TRUE(nek::is_volatile<void(*volatile)()>);
	STATIC_ASSERT_TRUE(nek::is_volatile<int* volatile>);
	STATIC_ASSERT_TRUE(nek::is_volatile<int volatile[]>);
	SUCCEED();
}

TEST(is_volatile_test, no)
{
	using namespace type_traits_test;
	STATIC_ASSERT_FALSE(nek::is_volatile<int>);
	STATIC_ASSERT_FALSE(nek::is_volatile<class_type>);
	STATIC_ASSERT_FALSE(nek::is_volatile<enum_type>);
	STATIC_ASSERT_FALSE(nek::is_volatile<union_type>);
	STATIC_ASSERT_FALSE(nek::is_volatile<void>);
	STATIC_ASSERT_FALSE(nek::is_volatile<int[]>);
	STATIC_ASSERT_FALSE(nek::is_volatile<void(*)()>);
	STATIC_ASSERT_FALSE(nek::is_volatile<int volatile*>);
	STATIC_ASSERT_FALSE(nek::is_volatile<int volatile&>);
	STATIC_ASSERT_FALSE(nek::is_volatile<int volatile&&>);
	SUCCEED();
}