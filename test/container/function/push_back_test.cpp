#include <nek/container/function/push_back.hpp>
#include <nek/utility/move.hpp>
#include <gtest/gtest.h>
#include <list>

TEST(push_back_test, lvalue)
{
    std::list<int> list;
    EXPECT_TRUE(list.empty());
    int a = 3;
    nek::push_back(list, a);
    EXPECT_EQ(1, list.size());
    EXPECT_EQ(3, list.front());
}

TEST(push_back_test, move)
{
    std::list<int> list;
    EXPECT_TRUE(list.empty());
    int a = 3;
    nek::push_back(list, nek::move(a));
    EXPECT_EQ(1, list.size());
    EXPECT_EQ(3, list.front());
}
