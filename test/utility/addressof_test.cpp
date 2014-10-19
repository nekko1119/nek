#include <nek/utility/addressof.hpp>
#include <gtest/gtest.h>

namespace
{
	struct addressable
	{
	public:
		addressable(int = 0)
		{
		}
	};

	struct never_use_type
	{
	};

	struct nonaddressable
	{
	public:
		nonaddressable(int = 0)
		{
		}

	private:
		never_use_type operator&() const;
	};
}

template <class T>
class addressof_test
	: public ::testing::Test
{
};

using types = ::testing::Types<
	int,
	addressable,
	nonaddressable
>;

TYPED_TEST_CASE(addressof_test, types);

TYPED_TEST(addressof_test, scalar)
{
	TypeParam* ptr = new TypeParam{};
	TypeParam& val = *ptr;
	EXPECT_EQ(ptr, nek::addressof(val));
	delete ptr;
}

TYPED_TEST(addressof_test, array)
{
	TypeParam arr[] = {1, 2, 3};
	TypeParam(*arr_ptr)[3] = &arr;
	EXPECT_EQ(arr_ptr, nek::addressof(arr));
}