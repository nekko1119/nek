#include <nek/algorithm/fill_n.hpp>
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

TEST(fill_n_test, byte)
{
    constexpr std::size_t size = 3;
    constexpr char value = 'n';
    constexpr char expected[] = {'n', 'n', 'n'};
    char buffer[size];
    nek::fill_n(buffer, size, value);
    EXPECT_TRUE(std::equal(buffer, buffer + size, expected));
}

TEST(fill_n_test, non_byte)
{
    constexpr std::size_t size = 3;
    constexpr int value = 42;
    std::vector<int> expected = {42, 42, 42};
    std::vector<int> buffer(3);
    nek::fill_n(buffer.begin(), size, value);
    EXPECT_TRUE(std::equal(buffer.begin(), buffer.end(), expected.begin()));
}
