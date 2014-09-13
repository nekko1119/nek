#include <nek/uninitialized/uninitialized_fill.hpp>
#include <gtest/gtest.h>

TEST(uninitialized_fill_test, normal)
{
  nek::allocator<int> alloc;
  int* buffer = alloc.allocate(3);
  nek::uninitialized_fill(buffer, buffer + 3, 42);
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(42, buffer[i]);
  }
  alloc.destroy(buffer);
  alloc.deallocate(buffer, 3);
}

TEST(uninitialized_fill_n, normal)
{
  nek::allocator<int> alloc;
  int* buffer =  alloc.allocate(3);
  nek::uninitialized_fill_n(buffer, 3, 42);
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(42, buffer[i]);
  }
  alloc.destroy(buffer);
  alloc.deallocate(buffer, 3);
}
