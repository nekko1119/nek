#include <nek/container/function/front.hpp>
#include <gtest/gtest.h>
#include <list>

TEST(front_test, list)
{
    std::list<int> l = {1, 2, 3};
    nek::front(l) = 10;
    EXPECT_EQ(10, nek::front(l));
}

TEST(front_test, const_list)
{
    std::list<int> const l = {1, 2, 3};
    EXPECT_EQ(1, nek::front(l));
}

TEST(front_test, array)
{
    int a[] = {1, 2, 3};
    nek::front(a) = 10;
    EXPECT_EQ(10, nek::front(a));
}

TEST(front_test, const_array)
{
    constexpr int a[] = {1, 2, 3};
    // TODO VC++ 14.0 RTM
    // static_assert(nek::front(a) == 1, "");
    EXPECT_EQ(1, nek::front(a));
}
