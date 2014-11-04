#include <nek/math/gcd.hpp>
#include <gtest/gtest.h>

TEST(gcd_test, normal)
{
	using nek::math::gcd;
	ASSERT_EQ(gcd(1, -1), 1);
	ASSERT_EQ(gcd(-1, 1), 1);
	ASSERT_EQ(gcd(-1, -1), 1);
	ASSERT_EQ(gcd(1, 1), 1);
	ASSERT_EQ(gcd(0, 0), 0);
	ASSERT_EQ(gcd(9, 0), 9);
	ASSERT_EQ(gcd(0, 7), 7);
	ASSERT_EQ(gcd(-9, 0), 9);
	ASSERT_EQ(gcd(0, -7), 7);
	ASSERT_EQ(gcd(9, 0), 9);
	ASSERT_EQ(gcd(42, 30), 6);
	ASSERT_EQ(gcd(6, -9), 3);
	ASSERT_EQ(gcd(-10, -10), 10);
	ASSERT_EQ(gcd(-25, -10), 5);
	ASSERT_EQ(gcd(3, 7), 1);
	ASSERT_EQ(gcd(8, 9), 1);
	ASSERT_EQ(gcd(-10, -10), 10);
}
