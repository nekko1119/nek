#include <nek/uninitialized/uninitialized_copy.hpp>
#include <gtest/gtest.h>

namespace
{
  struct mock
  {
    int n;

    mock()
      : n{42}
    {
    }
  };
}

class uninitialized_copy_test
  : public ::testing::Test
{
protected:
  char* buffer = nullptr;

  void SetUp() override
  {
    buffer = new char[sizeof(mock) * size()];
  }

  void TearDown() override
  {
    delete[] buffer;
    buffer = nullptr;
  }

  static constexpr int size()
  {
    return 3;
  }
};

TEST(uninitialized_copy_test, check)
{
}