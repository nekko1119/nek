#include <nek/mpl/eval_if.hpp>
#include <nek/mpl/identity.hpp>
#include <nek/mpl/bool.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"
namespace mpl = nek::mpl;

TEST(eval_if_test, true_)
{
  using actual_type = mpl::eval_if<mpl::true_, mpl::identity<char>, mpl::identity<long>>::type;
  using expected_type = char;
  STATIC_ASSERT_EQ(actual_type, expected_type);
}

TEST(eval_if_test, false_)
{
  using actual_type = mpl::eval_if<mpl::false_, mpl::identity<char>, mpl::identity<long>>::type;
  using expected_type = long;
  STATIC_ASSERT_EQ(actual_type, expected_type);
}

TEST(eval_if_c_test, true)
{
  using actual_type = mpl::eval_if_c<true, mpl::identity<char>, mpl::identity<long>>::type;
  using expected_type = char;
  STATIC_ASSERT_EQ(actual_type, expected_type);
}

TEST(eval_if_c_test, false)
{
  using actual_type = mpl::eval_if_c<false, mpl::identity<char>, mpl::identity<long>>::type;
  using expected_type = long;
  STATIC_ASSERT_EQ(actual_type, expected_type);
}
