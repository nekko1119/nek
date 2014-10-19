#include <nek/type_traits/is_enum.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

namespace
{
	enum class scoped_enum_type
	{
		a,
		b,
		c
	};
}

TEST(is_enum_test, initialize_true)
{
	using namespace type_traits_test;
	STATIC_ASSERT_TRUE(nek::is_enum<enum_type>);
	STATIC_ASSERT_EQ(nek::is_enum<enum_type>::type, nek::true_type);
	STATIC_ASSERT_EQ(nek::is_enum<enum_type>::value_type, bool);
	EXPECT_EQ(true, nek::is_enum<enum_type>());
	SUCCEED();
}

TEST(is_enum_test, initialize_false)
{
	STATIC_ASSERT_FALSE(nek::is_enum<int>);
	STATIC_ASSERT_EQ(nek::is_enum<int>::type, nek::false_type);
	STATIC_ASSERT_EQ(nek::is_enum<int>::value_type, bool);
	EXPECT_EQ(false, nek::is_enum<int>());
	SUCCEED();
}

TEST(is_enum_test, yes)
{
	using namespace type_traits_test;
	STATIC_ASSERT_TRUE(nek::is_enum<enum_type>);
	STATIC_ASSERT_TRUE(nek::is_enum<enum_type const>);
	STATIC_ASSERT_TRUE(nek::is_enum<enum_type volatile>);
	STATIC_ASSERT_TRUE(nek::is_enum<enum_type const volatile>);
	STATIC_ASSERT_TRUE(nek::is_enum<scoped_enum_type>);
	SUCCEED();
}

TEST(is_enum_test, no)
{
	using namespace type_traits_test;
	STATIC_ASSERT_FALSE(nek::is_enum<int>);
	STATIC_ASSERT_FALSE(nek::is_enum<void>);
	STATIC_ASSERT_FALSE(nek::is_enum<enum_type*>);
	STATIC_ASSERT_FALSE(nek::is_enum<enum_type[]>);
	STATIC_ASSERT_FALSE(nek::is_enum<enum_type&>);
	STATIC_ASSERT_FALSE(nek::is_enum<enum_type&&>);
	STATIC_ASSERT_FALSE(nek::is_enum<class_type>);
	STATIC_ASSERT_FALSE(nek::is_enum<union_type>);
	STATIC_ASSERT_FALSE(nek::is_enum<f1_type>);
	STATIC_ASSERT_FALSE(nek::is_enum<mf1_type>);
	SUCCEED();
}