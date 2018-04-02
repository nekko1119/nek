#include <nek/algorithm/max.hpp>
#include <gtest/gtest.h>

TEST(max_test, normal)
{
    int const a = 2;
    int const b = 3;
    int const& c = nek::max(a, b);
    EXPECT_EQ(b, c);
    EXPECT_EQ(&b, &c);
    int const& d = nek::max(b, a);
    EXPECT_EQ(b, d);
    EXPECT_EQ(&b, &d);
    int e = nek::max(c, d); // workaround. VS 2017 can not const reference.
    EXPECT_EQ(c, e);
    //EXPECT_EQ(&c, &e);
}
