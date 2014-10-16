#include <nek/iterator/advance.hpp>
#include <gtest/gtest.h>
#include <list>
#include <forward_list>

TEST(advance_test, random_access_iterator)
{
	int a[] = {1, 2, 3, 4};
	int* p = a;
	nek::advance(p, 2);
	EXPECT_EQ(3, *p);
}

TEST(advance_test, bidirectional_iterator)
{
	std::list<int> l = {1, 2, 3, 4};
	auto it = l.begin();
	nek::advance(it, 2);
	EXPECT_EQ(3, *it);
}

TEST(advance_test, forward_iterator)
{
	std::forward_list<int> l = {1, 2, 3, 4};
	auto it = l.begin();
	nek::advance(it, 2);
	EXPECT_EQ(3, *it);
}