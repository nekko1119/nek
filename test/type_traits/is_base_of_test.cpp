#include <nek/type_traits/is_base_of.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

namespace
{
	struct b
	{
		virtual ~b() {}
	};

	struct d
		: private b
	{
	};

	struct other
	{};
}

TEST(is_base_of_test, initialize_true)
{
	using actual_type = nek::is_base_of<b, d>;
	STATIC_ASSERT_TRUE(actual_type);
	STATIC_ASSERT_EQ(actual_type::type, nek::true_type);
	STATIC_ASSERT_EQ(actual_type::value_type, bool);
	EXPECT_EQ(true, actual_type());
}

TEST(is_base_of_test, initialize_false)
{
	using actual_type = nek::is_base_of<int, int>;
	STATIC_ASSERT_FALSE(actual_type);
	STATIC_ASSERT_EQ(actual_type::type, nek::false_type);
	STATIC_ASSERT_EQ(actual_type::value_type, bool);
	EXPECT_EQ(false, actual_type());
}

TEST(is_base_of_test, yes)
{
	using bd_type = nek::is_base_of<b, d>;
	using bb_type = nek::is_base_of<b, b>;
	using cvbd_type = nek::is_base_of<b const volatile, d>;
	using other_other_type = nek::is_base_of<other, other>;
	STATIC_ASSERT_TRUE(bd_type);
	STATIC_ASSERT_TRUE(bb_type);
	STATIC_ASSERT_TRUE(cvbd_type);
	STATIC_ASSERT_TRUE(other_other_type);
}

TEST(is_base_of_test, no)
{
	using int_int_type = nek::is_base_of<int, int>;
	using int_char_type = nek::is_base_of<int, char>;
	using b_other_type = nek::is_base_of<b, other>;
	using refb_d_type = nek::is_base_of<b&, d>;
	using rbrd_type = nek::is_base_of<b&, d&>;
	using pbpd_type = nek::is_base_of<b*, d*>;
	STATIC_ASSERT_FALSE(int_int_type);
	STATIC_ASSERT_FALSE(int_char_type);
	STATIC_ASSERT_FALSE(b_other_type);
	STATIC_ASSERT_FALSE(refb_d_type);
	STATIC_ASSERT_FALSE(rbrd_type);
	STATIC_ASSERT_FALSE(pbpd_type);
}
