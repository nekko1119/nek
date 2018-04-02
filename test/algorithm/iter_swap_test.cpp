#include <nek/algorithm/iter_swap.hpp>
#include <gtest/gtest.h>
#include <list>

TEST(iter_swap_test, pointer)
{
    // setup
    int a = 3;
    int b = 7;
    int* pa = &a;
    int* pb = &b;

    // exercise
    nek::iter_swap(pa, pb);

    // verify
    EXPECT_EQ(7, *pa);
    EXPECT_EQ(3, *pb);
    EXPECT_EQ(7, a);
    EXPECT_EQ(3, b);
}

TEST(iter_swap_test, list)
{
    // setup
    std::list<int> l = {3, 7};
    auto i = l.begin();
    auto j = ++l.begin();
    EXPECT_EQ(3, *i);
    EXPECT_EQ(7, *j);

    // exercise
    nek::iter_swap(i, j);

    // verify
    EXPECT_EQ(7, *i);
    EXPECT_EQ(3, *j);
}
