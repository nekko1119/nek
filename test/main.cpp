#include <gtest/gtest.h>
#include <nek/allocator/allocator.hpp>
#include <vector>

int main(int argc, char** argv)
{
  std::vector<int, nek::allocator<int>> v;
  v.reserve(10);
  v.resize(5);
  v.push_back(1);
  v.pop_back();
  v.shrink_to_fit();
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}