#include <nek/type_traits/is_signed.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(is_signed_test, initialize_true)
{
	STATIC_ASSERT_TRUE(nek::is_signed<int>);
	STATIC_ASSERT_EQ(nek::is_signed<int>::type, nek::true_type);
	STATIC_ASSERT_EQ(nek::is_signed<int>::value_type, bool);
	EXPECT_EQ(true, nek::is_signed<int>());
}

TEST(is_signed_test, initialize_false)
{
	STATIC_ASSERT_FALSE(nek::is_signed<void>);
	STATIC_ASSERT_EQ(nek::is_signed<void>::type, nek::false_type);
	STATIC_ASSERT_EQ(nek::is_signed<void>::value_type, bool);
	EXPECT_EQ(false, nek::is_signed<void>());
}

TEST(is_signed_test, yes)
{
	STATIC_ASSERT_TRUE(nek::is_signed<int>);
	STATIC_ASSERT_TRUE(nek::is_signed<float>);
	STATIC_ASSERT_TRUE(nek::is_signed<long double>);
	STATIC_ASSERT_TRUE(nek::is_signed<char>);
	STATIC_ASSERT_TRUE(nek::is_signed<signed char>);
}

TEST(is_signed_test, no)
{
	STATIC_ASSERT_FALSE(nek::is_signed<unsigned char>);
	STATIC_ASSERT_FALSE(nek::is_signed<std::nullptr_t>);
	STATIC_ASSERT_FALSE(nek::is_signed<void>);
	STATIC_ASSERT_FALSE(nek::is_signed<bool>);
	STATIC_ASSERT_FALSE(nek::is_signed<int*>);
}
