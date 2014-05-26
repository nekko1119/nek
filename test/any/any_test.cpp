#include <nek/any.hpp>
#include <gtest/gtest.h>

namespace
{
  class dummy
  {
  };
}

TEST(any_test, default_constructor)
{
  nek::any instance;

  // verify
  EXPECT_TRUE(instance.is_empty());
  EXPECT_EQ(typeid(void), instance.type());
}

TEST(any_test, convert_construct)
{
  int expected = 1;
  nek::any instance = expected;
  
  // verify
  EXPECT_FALSE(instance.is_empty());
  EXPECT_EQ(typeid(int), instance.type());
  EXPECT_EQ(nullptr, nek::any_cast<dummy>(&instance));
  ASSERT_NE(nullptr, nek::any_cast<int>(&instance));
  EXPECT_EQ(expected, *(nek::any_cast<int>(&instance)));
  EXPECT_NE(&expected, nek::any_cast<int>(&instance));
}