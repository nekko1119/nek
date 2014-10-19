#include <nek/type_traits/is_constructible.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "static_assert.hpp"

namespace
{
	struct x
	{
		explicit x(int) {}
		x(x const&) = delete;
	};

	class y
	{
		y() {}
	};

	struct base
	{
		virtual ~base() {}
	};

	struct derived
		: public base
	{
	};
}

TEST(is_constructible_test, initialize_true)
{
	using actual_type = nek::is_constructible<int, int>;
	STATIC_ASSERT_TRUE(actual_type);
	STATIC_ASSERT_EQ(actual_type::type, nek::true_type);
	STATIC_ASSERT_EQ(actual_type::value_type, bool);
	EXPECT_EQ(true, actual_type());
}

TEST(is_constructible_test, initialize_false)
{
	using actual_type = nek::is_constructible<int, void>;
	STATIC_ASSERT_FALSE(actual_type);
	STATIC_ASSERT_EQ(actual_type::type, nek::false_type);
	STATIC_ASSERT_EQ(actual_type::value_type, bool);
	EXPECT_EQ(false, actual_type());
}

TEST(is_constructible_test, yes)
{
	using i_type = nek::is_constructible<int>;
	using ii_type = nek::is_constructible<int, int>;
	using id_type = nek::is_constructible<int, double>;
	using xi_type = nek::is_constructible<x, int>;
	using iter_type = std::vector<double>::iterator;
	using vin_type = nek::is_constructible<std::vector<int>, std::initializer_list<int>>;
	using vii_type = nek::is_constructible<std::vector<int>, iter_type, iter_type>; // vector(Iterator, Iterator)
	using bd_type = nek::is_constructible<base, derived>;
	using pbpd_type = nek::is_constructible<base*, derived*>;
	using rbrd_type = nek::is_constructible<base&, derived&>;
	using brd_type = nek::is_constructible<base, derived&>;
	STATIC_ASSERT_TRUE(i_type);
	STATIC_ASSERT_TRUE(ii_type);
	STATIC_ASSERT_TRUE(id_type);
	STATIC_ASSERT_TRUE(xi_type);
	STATIC_ASSERT_TRUE(vin_type);
	STATIC_ASSERT_TRUE(vii_type);
	STATIC_ASSERT_TRUE(bd_type);
	STATIC_ASSERT_TRUE(pbpd_type);
	STATIC_ASSERT_TRUE(rbrd_type);
	STATIC_ASSERT_TRUE(brd_type);
}

TEST(is_constructible_test, no)
{
	using xx_type = nek::is_constructible<x, x>;
	using fi_type = nek::is_constructible<void(*)(int), int>;
	using vi_type = nek::is_constructible<void, int>;
	using y_type = nek::is_constructible<y>;
	using vvv_type = nek::is_constructible<std::vector<int>, void, void>;
	using rbd_type = nek::is_constructible<base&, derived>;

	STATIC_ASSERT_FALSE(xx_type);
	STATIC_ASSERT_FALSE(fi_type);
	STATIC_ASSERT_FALSE(vi_type);
	STATIC_ASSERT_FALSE(y_type);
	STATIC_ASSERT_FALSE(vvv_type);
	STATIC_ASSERT_FALSE(rbd_type);
}
