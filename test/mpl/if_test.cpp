#include <nek/mpl/if.hpp>
#include <nek/mpl/bool.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"
namespace mpl = nek::mpl;

TEST(if_test, true_)
{
  using actual_type = mpl::if_<mpl::true_, char, long>::type;
  using expected_type = char;
  STATIC_ASSERT_EQ(actual_type, expected_type);
}

TEST(if_test, false_)
{
  using actual_type = mpl::if_<mpl::false_, char, long>::type;
  using expected_type = long;
  STATIC_ASSERT_EQ(actual_type, expected_type);
}

TEST(if_c_test, true)
{
  using actual_type = mpl::if_c<true, char, long>::type;
  using expected_type = char;
  STATIC_ASSERT_EQ(actual_type, expected_type);
}

TEST(if_c_test, false)
{
  using actual_type = mpl::if_c<false, char, long>::type;
  using expected_type = long;
  STATIC_ASSERT_EQ(actual_type, expected_type);
}