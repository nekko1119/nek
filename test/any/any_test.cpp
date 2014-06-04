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

  // values should be equal, but addresses should not be equal
  EXPECT_EQ(expected, *(nek::any_cast<int>(&instance)));
  EXPECT_NE(&expected, nek::any_cast<int>(&instance));
}

TEST(any_test, copy_constructor)
{
  int expected = 1;
  nek::any original = expected;
  nek::any instance = original;

  // verify
  EXPECT_FALSE(instance.is_empty());
  EXPECT_EQ(original.type(), instance.type());

  EXPECT_EQ(nullptr, nek::any_cast<dummy>(&instance));
  ASSERT_NE(nullptr, nek::any_cast<int>(&instance));

  // values should be equal, but addresses should not be equal
  EXPECT_EQ(nek::any_cast<int>(original), nek::any_cast<int>(instance));
  EXPECT_NE(nek::any_cast<int>(&original), nek::any_cast<int>(&instance));
}

TEST(any_test, bad_cast)
{
  int stub = 0;
  nek::any sut = stub;
  EXPECT_THROW(nek::any_cast<dummy>(sut);, nek::bad_any_cast_exception);
}