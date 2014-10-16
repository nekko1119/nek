#include <nek/container/function/size.hpp>
#include <gtest/gtest.h>
#include <list>

TEST(container_size_test, array)
{
	int a[5];
	EXPECT_EQ(5, nek::size(a));
}

TEST(container_size_test, list)
{
	std::list<int> l = {1, 2, 3, 4, 5};
	EXPECT_EQ(5, nek::size(l));
}