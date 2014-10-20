#include <algorithm>
#include <nek/algorithm/move.hpp>
#include <gtest/gtest.h>

TEST(move_test, raw_array)
{
	// setup
	int src[4] = {1, 2, 3, 4};
	int dest[4] = {};

	// exercise
	nek::move(src, src + 4, dest);

	// verify
	EXPECT_EQ(1, dest[0]);
	EXPECT_EQ(2, dest[1]);
	EXPECT_EQ(3, dest[2]);
	EXPECT_EQ(4, dest[3]);
}

TEST(move_test, dynamic_array)
{
	// setup
	int* src = new int[4];
	src[0] = 1;
	src[1] = 2;
	src[2] = 3;
	src[3] = 4;
	int* dest = new int[4]{};

	// exercise
	nek::move(src, src + 4, dest);

	// verify
	EXPECT_EQ(1, dest[0]);
	EXPECT_EQ(2, dest[1]);
	EXPECT_EQ(3, dest[2]);
	EXPECT_EQ(4, dest[3]);

	// tear down
	delete[] src;
	delete[] dest;
}

TEST(move_test, forward)
{
	int a[] = {0, 1, 2, 3};
	int expected[] = {1, 2, 3, 3};
	nek::move(a + 1, a + 4, a);
	EXPECT_TRUE(std::equal(a, a + 4, expected));
}

namespace
{
	struct noncopyable
	{
		int x;
		noncopyable(): x{0} {}
		noncopyable(int x): x{x} {}
		noncopyable(noncopyable const&) = delete;
		noncopyable& operator=(noncopyable const&) = delete;
		friend bool operator==(noncopyable const& l, noncopyable const& r) noexcept
		{
			return l.x == r.x;
		}
	};
}

TEST(move_test, noncopyable)
{
	noncopyable a[] = {0, 1, 2, 3};
	noncopyable expected[] = {1, 2, 3, 3};
	nek::move(a + 1, a + 4, a);
	EXPECT_TRUE(std::equal(a, a + 4, expected));
}
