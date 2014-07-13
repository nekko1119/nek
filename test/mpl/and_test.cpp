#include <nek/mpl/and.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"

TEST(and_c_test, true)
{
  namespace mpl = nek::mpl;
  using and1 = mpl::and_c<true>;
  STATIC_ASSERT_TRUE(and1);
  using and2 = mpl::and_c<true, true>;
  STATIC_ASSERT_TRUE(and2);
  using and3 = mpl::and_c<true, true, true>;
  STATIC_ASSERT_TRUE(and3);
  using and4 = mpl::and_c<true, true, true>;
  STATIC_ASSERT_TRUE(and4);
}

TEST(and_c_test, false)
{
  namespace mpl = nek::mpl;
  using and1 = mpl::and_c<false>;
  STATIC_ASSERT_FALSE(and1);
  using and2_1 = mpl::and_c<true, false>;
  STATIC_ASSERT_FALSE(and2_1);
  using and2_2 = mpl::and_c<true, false>;
  STATIC_ASSERT_FALSE(and2_2);
  using and2_3 = mpl::and_c<false, false>;
  STATIC_ASSERT_FALSE(and2_3);
  using and3_1 = mpl::and_c<true, true, false>;
  STATIC_ASSERT_FALSE(and3_1);
  using and3_2 = mpl::and_c<true, false, true>;
  STATIC_ASSERT_FALSE(and3_2);
  using and3_3 = mpl::and_c<true, false, false>;
  STATIC_ASSERT_FALSE(and3_3);
  using and3_4 = mpl::and_c<false, true, true>;
  STATIC_ASSERT_FALSE(and3_4);
  using and3_5 = mpl::and_c<false, true, false>;
  STATIC_ASSERT_FALSE(and3_5);
  using and3_6 = mpl::and_c<false, false, true>;
  STATIC_ASSERT_FALSE(and3_6);
  using and3_7 = mpl::and_c<false, false, false>;
  STATIC_ASSERT_FALSE(and3_7);
}

TEST(and_test, true_)
{
  namespace mpl = nek::mpl;
  using and1 = mpl::and_<mpl::true_>;
  STATIC_ASSERT_TRUE(and1);
  using and2 = mpl::and_<mpl::true_, mpl::true_>;
  STATIC_ASSERT_TRUE(and2);
  using and3 = mpl::and_<mpl::true_, mpl::true_, mpl::true_>;
  STATIC_ASSERT_TRUE(and3);
  using and4 = mpl::and_<mpl::true_, mpl::true_, mpl::true_>;
  STATIC_ASSERT_TRUE(and4);
}

TEST(and_test, false_)
{
  namespace mpl = nek::mpl;
  using and1 = mpl::and_<mpl::false_>;
  STATIC_ASSERT_FALSE(and1);
  using and2_1 = mpl::and_<mpl::true_, mpl::false_>;
  STATIC_ASSERT_FALSE(and2_1);
  using and2_2 = mpl::and_<mpl::true_, mpl::false_>;
  STATIC_ASSERT_FALSE(and2_2);
  using and2_3 = mpl::and_<mpl::false_, mpl::false_>;
  STATIC_ASSERT_FALSE(and2_3);
  using and3_1 = mpl::and_<mpl::true_, mpl::true_, mpl::false_>;
  STATIC_ASSERT_FALSE(and3_1);
  using and3_2 = mpl::and_<mpl::true_, mpl::false_, mpl::false_>;
  STATIC_ASSERT_FALSE(and3_2);
  using and3_3 = mpl::and_<mpl::true_, mpl::false_, mpl::false_>;
  STATIC_ASSERT_FALSE(and3_3);
  using and3_4 = mpl::and_<mpl::false_, mpl::true_, mpl::true_>;
  STATIC_ASSERT_FALSE(and3_4);
  using and3_5 = mpl::and_<mpl::false_, mpl::true_, mpl::false_>;
  STATIC_ASSERT_FALSE(and3_5);
  using and3_6 = mpl::and_<mpl::false_, mpl::false_, mpl::true_>;
  STATIC_ASSERT_FALSE(and3_6);
  using and3_7 = mpl::and_<mpl::false_, mpl::false_, mpl::false_>;
  STATIC_ASSERT_FALSE(and3_7);
}