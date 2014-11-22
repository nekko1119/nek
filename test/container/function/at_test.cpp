#include <nek/container/function/at.hpp>
#include <gtest/gtest.h>
#include <vector>

TEST(at_test, normal)
{
    std::vector<int> v = {1, 2, 3};
    nek::at(v, 0) = 10;
    EXPECT_EQ(10, *v.begin());
    auto const f = [&v](){ nek::at(v, 4); };
    EXPECT_THROW(f(), std::out_of_range);
}

TEST(at_test, const_at)
{
    std::vector<int> const v = {1, 2, 3};
    EXPECT_EQ(1, nek::at(v, 0));
    auto const f = [&v](){ nek::at(v, 4); };
    EXPECT_THROW(f(), std::out_of_range);
}

TEST(cat_test, normal)
{
    std::vector<int> const v = {1, 2, 3};
    EXPECT_EQ(1, nek::cat(v, 0));
    auto const f = [&v](){ nek::cat(v, 4); };
    EXPECT_THROW(f(), std::out_of_range);
}
