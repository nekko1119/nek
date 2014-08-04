#include <nek/uninitialized/uninitialized_move.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <string>

struct mock
{
  std::string log = "";

  mock() = default;
  mock(mock const&) = delete;
  mock& operator=(mock const&) = delete;
  mock(mock&&)
  {
    log += "move ctor";
  }
  mock& operator=(mock&&)
  {
    log += "move assgin";
  }
};

TEST(uninitialized_test, default_allocator)
{
  mock mocks[3] = {};
  mock* buf = new mock[3];
  nek::uninitialized_move(mocks + 0, mocks + 3, buf);
  EXPECT_EQ("move ctor", buf[0].log);
  EXPECT_EQ("move ctor", buf[1].log);
  EXPECT_EQ("move ctor", buf[2].log);
  delete[] buf;
}


TEST(uninitialized_test, custom_allocator)
{
  mock mocks[3] = {};
  mock* buf = new mock[3];
  nek::uninitialized_move(mocks + 0, mocks + 3, buf, std::allocator<mock>{});
  EXPECT_EQ("move ctor", buf[0].log);
  EXPECT_EQ("move ctor", buf[1].log);
  EXPECT_EQ("move ctor", buf[2].log);
  delete[] buf;
}