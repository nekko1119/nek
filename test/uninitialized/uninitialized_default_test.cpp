#include <nek/uninitialized/uninitialized_default.hpp>
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

class uninitialized_default_test
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

TEST_F(uninitialized_default_test, normal)
{
  // setup
  mock* first = reinterpret_cast<mock*>(buffer);
  ASSERT_NE(nullptr, first);

  // exercise
  nek::uninitialized_default_n(first, size());

  // verify
  for (int i = 0; i < size(); ++i)
  {
    EXPECT_EQ(42, first[i].n);
  }
}