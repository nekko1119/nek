#include <nek/algorithm/min.hpp>
#include <gtest/gtest.h>

TEST(min_test, normal)
{
    int const a = 2;
    int const b = 3;
    int const& c = nek::min(a, b);
    EXPECT_EQ(a, c);
    EXPECT_EQ(&a, &c);
    int const& d = nek::min(b, a);
    EXPECT_EQ(a, d);
    EXPECT_EQ(&a, &d);
    int const& e = nek::min(c, d);
    EXPECT_EQ(c, e);
    EXPECT_EQ(&c, &e);
}