#include <nek/container/function/back.hpp>
#include <gtest/gtest.h>
#include <list>

TEST(back_test, list)
{
    std::list<int> const l = {1, 2, 3};
    EXPECT_EQ(3, nek::back(l));
}

TEST(back_test, array)
{
    constexpr int a[] = {1, 2, 3};
    static_assert(3 == nek::back(a), "nek::back can apply on complie time");
    EXPECT_EQ(3, nek::back(a));
}
