#include <nek/type_traits/is_class.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_class_test, initialize_true)
{
	using namespace type_traits_test;
	STATIC_ASSERT_TRUE(nek::is_class<class_type>);
	STATIC_ASSERT_EQ(nek::is_class<class_type>::type, nek::true_type);
	STATIC_ASSERT_EQ(nek::is_class<class_type>::value_type, bool);
	EXPECT_EQ(true, nek::is_class<class_type>());
	SUCCEED();
}

TEST(is_class_test, initialize_false)
{
	STATIC_ASSERT_FALSE(nek::is_class<int>);
	STATIC_ASSERT_EQ(nek::is_class<int>::type, nek::false_type);
	STATIC_ASSERT_EQ(nek::is_class<int>::value_type, bool);
	EXPECT_EQ(false, nek::is_class<int>());
	SUCCEED();
}

TEST(is_class_test, yes)
{
	using namespace type_traits_test;
	STATIC_ASSERT_TRUE(nek::is_class<class_type>);
	STATIC_ASSERT_TRUE(nek::is_class<class_type const>);
	STATIC_ASSERT_TRUE(nek::is_class<class_type volatile>);
	STATIC_ASSERT_TRUE(nek::is_class<class_type const volatile>);
	SUCCEED();
}

TEST(is_class_test, no)
{
	using namespace type_traits_test;
	STATIC_ASSERT_FALSE(nek::is_class<int>);
	STATIC_ASSERT_FALSE(nek::is_class<void>);
	STATIC_ASSERT_FALSE(nek::is_class<class_type*>);
	STATIC_ASSERT_FALSE(nek::is_class<class_type[]>);
	STATIC_ASSERT_FALSE(nek::is_class<class_type&>);
	STATIC_ASSERT_FALSE(nek::is_class<class_type&&>);
	STATIC_ASSERT_FALSE(nek::is_class<enum_type>);
	STATIC_ASSERT_FALSE(nek::is_class<union_type>);
	STATIC_ASSERT_FALSE(nek::is_class<f1_type>);
	STATIC_ASSERT_FALSE(nek::is_class<mf1_type>);
	SUCCEED();
}