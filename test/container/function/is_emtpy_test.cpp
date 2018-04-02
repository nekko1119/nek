#include <nek/container/container_traits/adapted/std_container.hpp>
#include <nek/container/function/is_empty.hpp>
#include <gtest/gtest.h>
#include <list>

TEST(container_is_empty, array)
{
    int emp[1];
    // int emp0[0]; // can not be 0
    EXPECT_FALSE(nek::is_empty(emp));
}

TEST(container_is_empty, list)
{
    std::list<int> l;
    EXPECT_TRUE(nek::is_empty(l));
    l.push_back(42);
    EXPECT_FALSE(nek::is_empty(l));
}
