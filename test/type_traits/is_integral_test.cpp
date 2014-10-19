#include <nek/type_traits/is_integral.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_integral_test, initialize_true)
{
	STATIC_ASSERT_TRUE(nek::is_integral<int>);
	STATIC_ASSERT_EQ(nek::is_integral<int>::type, nek::true_type);
	STATIC_ASSERT_EQ(nek::is_integral<int>::value_type, bool);
	EXPECT_EQ(true, nek::is_integral<int>());
	SUCCEED();
}

TEST(is_integral_test, initialize_false)
{
	STATIC_ASSERT_FALSE(nek::is_integral<double>);
	STATIC_ASSERT_EQ(nek::is_integral<double>::type, nek::false_type);
	STATIC_ASSERT_EQ(nek::is_integral<double>::value_type, bool);
	EXPECT_EQ(false, nek::is_integral<double>());
	SUCCEED();
}

TEST(is_integral_test, yes)
{
	STATIC_ASSERT_TRUE(nek::is_integral<bool>);
	STATIC_ASSERT_TRUE(nek::is_integral<char>);
	STATIC_ASSERT_TRUE(nek::is_integral<signed char>);
	STATIC_ASSERT_TRUE(nek::is_integral<unsigned char>);
	STATIC_ASSERT_TRUE(nek::is_integral<wchar_t>);
	STATIC_ASSERT_TRUE(nek::is_integral<short>);
	STATIC_ASSERT_TRUE(nek::is_integral<unsigned short>);
	STATIC_ASSERT_TRUE(nek::is_integral<int>);
	STATIC_ASSERT_TRUE(nek::is_integral<unsigned int>);
	STATIC_ASSERT_TRUE(nek::is_integral<long>);
	STATIC_ASSERT_TRUE(nek::is_integral<unsigned long>);
	STATIC_ASSERT_TRUE(nek::is_integral<long long>);
	STATIC_ASSERT_TRUE(nek::is_integral<unsigned long long>);
	STATIC_ASSERT_TRUE(nek::is_integral<int const>);
	STATIC_ASSERT_TRUE(nek::is_integral<int volatile>);
	STATIC_ASSERT_TRUE(nek::is_integral<int const volatile>);
	SUCCEED();
}

TEST(is_integral_test, no)
{
	using namespace type_traits_test;
	STATIC_ASSERT_FALSE(nek::is_integral<float>);
	STATIC_ASSERT_FALSE(nek::is_integral<void>);
	STATIC_ASSERT_FALSE(nek::is_integral<int*>);
	STATIC_ASSERT_FALSE(nek::is_integral<int[]>);
	STATIC_ASSERT_FALSE(nek::is_integral<int&>);
	STATIC_ASSERT_FALSE(nek::is_integral<int&&>);
	STATIC_ASSERT_FALSE(nek::is_integral<class_type>);
	STATIC_ASSERT_FALSE(nek::is_integral<f1_type>);
	STATIC_ASSERT_FALSE(nek::is_integral<mf1_type>);
	SUCCEED();
}