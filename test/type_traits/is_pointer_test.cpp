#include <nek/type_traits/is_pointer.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_pointer_test, initialize_true)
{
	using namespace type_traits_test;
	STATIC_ASSERT_TRUE(nek::is_pointer<int*>);
	STATIC_ASSERT_EQ(nek::is_pointer<int*>::type, nek::true_type);
	STATIC_ASSERT_EQ(nek::is_pointer<int*>::value_type, bool);
	EXPECT_EQ(true, nek::is_pointer<int*>());
	SUCCEED();
}

TEST(is_pointer_test, initialize_false)
{
	STATIC_ASSERT_FALSE(nek::is_pointer<int>);
	STATIC_ASSERT_EQ(nek::is_pointer<int>::type, nek::false_type);
	STATIC_ASSERT_EQ(nek::is_pointer<int>::value_type, bool);
	EXPECT_EQ(false, nek::is_pointer<int>());
	SUCCEED();
}

TEST(is_pointer_test, yes)
{
	using namespace type_traits_test;
	STATIC_ASSERT_TRUE(nek::is_pointer<int*>);
	STATIC_ASSERT_TRUE(nek::is_pointer<int**>);
	STATIC_ASSERT_TRUE(nek::is_pointer<int const*>);
	STATIC_ASSERT_TRUE(nek::is_pointer<int volatile*>);
	STATIC_ASSERT_TRUE(nek::is_pointer<int const volatile*>);
	STATIC_ASSERT_TRUE(nek::is_pointer<int* const>);
	STATIC_ASSERT_TRUE(nek::is_pointer<int* volatile>);
	STATIC_ASSERT_TRUE(nek::is_pointer<int* const volatile>);
	STATIC_ASSERT_TRUE(nek::is_pointer<f1_type>);
	STATIC_ASSERT_TRUE(nek::is_pointer<int(*)[]>);
	SUCCEED();
}

TEST(is_pointer_test, no)
{
	using namespace type_traits_test;
	STATIC_ASSERT_FALSE(nek::is_pointer<int>);
	STATIC_ASSERT_FALSE(nek::is_pointer<void>);
	STATIC_ASSERT_FALSE(nek::is_pointer<std::nullptr_t>);
	STATIC_ASSERT_FALSE(nek::is_pointer<int&>);
	STATIC_ASSERT_FALSE(nek::is_pointer<int&&>);
	STATIC_ASSERT_FALSE(nek::is_pointer<int[]>);
	STATIC_ASSERT_FALSE(nek::is_pointer<int(&)[]>);
	STATIC_ASSERT_FALSE(nek::is_pointer<void()>);
	STATIC_ASSERT_FALSE(nek::is_pointer<void(&)()>);
	STATIC_ASSERT_FALSE(nek::is_pointer<int*&>);
	STATIC_ASSERT_FALSE(nek::is_pointer<int(&)[]>);
	STATIC_ASSERT_FALSE(nek::is_pointer<mf1_type>);

	SUCCEED();
}