#include <string>
#include <type_traits>
#include <nek/utility/forward.hpp>
#include <gtest/gtest.h>

namespace
{
  struct forward_logging_mock
  {
    std::string log = "";
    forward_logging_mock() = default;
    forward_logging_mock(forward_logging_mock const&)
    {
      log += "copy";
    }

    forward_logging_mock(forward_logging_mock&&)
    {
      log += "move";
    }

    forward_logging_mock& operator=(forward_logging_mock const&)
    {
      log += "copy op";
      return *this;
    }

    forward_logging_mock& operator=(forward_logging_mock&&)
    {
      log += "move op";
      return *this;
    }
  };
}

TEST(forward_test, return_rvalue_reference_if_template_argement_is_value_type)
{
  forward_logging_mock f;
  decltype(auto) actual = nek::forward<forward_logging_mock>(f);
  EXPECT_EQ("", actual.log);
  EXPECT_TRUE(std::is_rvalue_reference<decltype(actual)>::value);
}

TEST(forward_test, return_rvalue_reference_if_template_argement_is_rvalue_reference_type)
{
  forward_logging_mock f;
  decltype(auto) actual = nek::forward<forward_logging_mock&&>(f);
  EXPECT_EQ("", actual.log);
  EXPECT_TRUE(std::is_rvalue_reference<decltype(actual)>::value);
}

TEST(forward_test, return_lvalue_reference_if_template_argement_is_lvalue_reference_type)
{
  forward_logging_mock f;
  decltype(auto) actual = nek::forward<forward_logging_mock&>(f);
  EXPECT_EQ("", actual.log);
  EXPECT_TRUE(std::is_lvalue_reference<decltype(actual)>::value);
}