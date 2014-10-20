#include <algorithm>
#include <nek/algorithm/copy.hpp>
#include <gtest/gtest.h>

TEST(copy_test, raw_array)
{
	// setup
	int src[4] = {1, 2, 3, 4};
	int dest[4] = {};

	// exercise
	nek::copy(src, src + 4, dest);

	// verify
	EXPECT_EQ(1, dest[0]);
	EXPECT_EQ(2, dest[1]);
	EXPECT_EQ(3, dest[2]);
	EXPECT_EQ(4, dest[3]);
	EXPECT_EQ(1, src[0]);
	EXPECT_EQ(2, src[1]);
	EXPECT_EQ(3, src[2]);
	EXPECT_EQ(4, src[3]);
}

TEST(copy_test, dynamic_array)
{
	// setup
	int* src = new int[4];
	src[0] = 1;
	src[1] = 2;
	src[2] = 3;
	src[3] = 4;
	int* dest = new int[4]{};

	// exercise
	nek::copy(src, src + 4, dest);

	// verify
	EXPECT_EQ(1, dest[0]);
	EXPECT_EQ(2, dest[1]);
	EXPECT_EQ(3, dest[2]);
	EXPECT_EQ(4, dest[3]);
	EXPECT_EQ(1, src[0]);
	EXPECT_EQ(2, src[1]);
	EXPECT_EQ(3, src[2]);
	EXPECT_EQ(4, src[3]);

	// tear down
	delete[] src;
	delete[] dest;
}

TEST(copy_test, forward)
{
	int a[] = {0, 1, 2, 3};
	int expected[] = {1, 2, 3, 3};
	nek::copy(a + 1, a + 4, a);
	EXPECT_TRUE(std::equal(a, a + 4, expected));
}
