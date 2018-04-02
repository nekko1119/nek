#include <nek/container/function/clear.hpp>
#include <gtest/gtest.h>
#include <vector>

TEST(clear_test, normal)
{
    std::vector<int> v = {1, 2, 3};
    nek::clear(v);
    EXPECT_TRUE(v.empty());
}
