#include <nek/container/function/data.hpp>
#include <gtest/gtest.h>
#include <string>

TEST(data_test, container)
{
    std::string s = "abcedf";
    auto data = nek::data(s);
    EXPECT_EQ(s.data(), data);
    std::string const cs = "vwxyz";
    auto const cdata = nek::data(cs);
    EXPECT_EQ(cs.data(), cdata);
}

TEST(data_test, array)
{
    int a[] = {1, 2, 3};
    auto data = nek::data(a);
    EXPECT_EQ(a, data);
    int const ca[] = {1, 2, 3};
    auto const cdata = nek::data(ca);
    EXPECT_EQ(ca, cdata);
}
