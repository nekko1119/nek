#include <nek/type_traits/is_byte.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(is_byte_test, initialize_true)
{
	STATIC_ASSERT_TRUE(nek::is_byte<char>);
	STATIC_ASSERT_EQ(nek::is_byte<char>::type, nek::true_type);
	STATIC_ASSERT_EQ(nek::is_byte<char>::value_type, bool);
	EXPECT_EQ(true, nek::is_byte<char>());
	SUCCEED();
}

TEST(is_byte_test, initialize_false)
{
	STATIC_ASSERT_FALSE(nek::is_byte<int>);
	STATIC_ASSERT_EQ(nek::is_byte<int>::type, nek::false_type);
	STATIC_ASSERT_EQ(nek::is_byte<int>::value_type, bool);
	EXPECT_EQ(false, nek::is_byte<int>());
	SUCCEED();
}

TEST(is_byte_test, yes)
{
	STATIC_ASSERT_TRUE(nek::is_byte<char>);
	STATIC_ASSERT_TRUE(nek::is_byte<signed char>);
	STATIC_ASSERT_TRUE(nek::is_byte<unsigned char>);
}

TEST(is_byte_test, no)
{
	STATIC_ASSERT_FALSE(nek::is_byte<const char>);
	STATIC_ASSERT_FALSE(nek::is_byte<char*>);
	STATIC_ASSERT_FALSE(nek::is_byte<int>);
	STATIC_ASSERT_FALSE(nek::is_byte<wchar_t>);
	STATIC_ASSERT_FALSE(nek::is_byte<void>);
	STATIC_ASSERT_FALSE(nek::is_byte<char16_t>);
	STATIC_ASSERT_FALSE(nek::is_byte<char32_t>);
	STATIC_ASSERT_FALSE(nek::is_byte<char[]>);
}
