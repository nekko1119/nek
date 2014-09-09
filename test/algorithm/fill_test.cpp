#include <nek/algorithm/fill.hpp>
#include <gtest/gtest.h>
#include <algorithm>
#include <vector>

TEST(fill_test, byte)
{
  constexpr std::size_t size = 3;
  constexpr char value = 'n';
  constexpr char expected[] = {'n', 'n', 'n'};
  char buffer[size];
  nek::fill(buffer, buffer + size, value);
  EXPECT_TRUE(std::equal(buffer, buffer + size, expected));
}

TEST(fill_test, non_byte)
{
  constexpr std::size_t size = 3;
  constexpr int value = 42;
  std::vector<int> expected = {42, 42, 42};
  std::vector<int> buffer(3);
  nek::fill(buffer.begin(), buffer.end(), value);
  EXPECT_TRUE(std::equal(buffer.begin(), buffer.end(), expected.begin()));
}
