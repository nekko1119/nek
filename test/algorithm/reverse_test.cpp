#include <nek/algorithm/reverse.hpp>
#include <gtest/gtest.h>
#include <list>

TEST(reverse_test, array)
{
    int a[] = {1, 2, 3, 4};

    nek::reverse(a, a + 4);

    EXPECT_EQ(4, a[0]);
    EXPECT_EQ(3, a[1]);
    EXPECT_EQ(2, a[2]);
    EXPECT_EQ(1, a[3]);
}

TEST(reverse_test, list)
{
    std::list<int> l = {1, 2, 3, 4};

    nek::reverse(l.begin(), l.end());

    auto it = l.begin();
    EXPECT_EQ(4, *it++);
    EXPECT_EQ(3, *it++);
    EXPECT_EQ(2, *it++);
    EXPECT_EQ(1, *it++);
}