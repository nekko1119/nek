#include <nek/mpl/or.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"

TEST(or_c_test, true)
{
  namespace mpl = nek::mpl;
  using or1 = mpl::or_c<true>;
  STATIC_ASSERT_TRUE(or1);
  using or2_1 = mpl::or_c<true, false>;
  STATIC_ASSERT_TRUE(or2_1);
  using or2_2 = mpl::or_c<false, true>;
  STATIC_ASSERT_TRUE(or2_2);
  using or2_3 = mpl::or_c<true, true>;
  STATIC_ASSERT_TRUE(or2_3);
  using or3_1 = mpl::or_c<true, true, false>;
  STATIC_ASSERT_TRUE(or3_1);
  using or3_2 = mpl::or_c<true, false, true>;
  STATIC_ASSERT_TRUE(or3_2);
  using or3_3 = mpl::or_c<true, false, false>;
  STATIC_ASSERT_TRUE(or3_3);
  using or3_4 = mpl::or_c<false, true, true>;
  STATIC_ASSERT_TRUE(or3_4);
  using or3_5 = mpl::or_c<false, true, false>;
  STATIC_ASSERT_TRUE(or3_5);
  using or3_6 = mpl::or_c<false, false, true>;
  STATIC_ASSERT_TRUE(or3_6);
  using or3_7 = mpl::or_c<true, true, true>;
  STATIC_ASSERT_TRUE(or3_7);
}

TEST(or_c_test, false)
{
  namespace mpl = nek::mpl;
  using or1 = mpl::or_c<false>;
  STATIC_ASSERT_FALSE(or1);
  using or2 = mpl::or_c<false, false>;
  STATIC_ASSERT_FALSE(or2);
  using or3 = mpl::or_c<false, false, false>;
  STATIC_ASSERT_FALSE(or3);
  using or4 = mpl::or_c<false, false, false, false>;
  STATIC_ASSERT_FALSE(or4);
}

TEST(or_test, true_)
{
  namespace mpl = nek::mpl;
  using or1 = mpl::or_<mpl::true_>;
  STATIC_ASSERT_TRUE(or1);
  using or2_1 = mpl::or_<mpl::true_, mpl::false_>;
  STATIC_ASSERT_TRUE(or2_1);
  using or2_2 = mpl::or_<mpl::false_, mpl::true_>;
  STATIC_ASSERT_TRUE(or2_2);
  using or2_3 = mpl::or_<mpl::true_, mpl::true_>;
  STATIC_ASSERT_TRUE(or2_3);
  using or3_1 = mpl::or_<mpl::true_, mpl::true_, mpl::false_>;
  STATIC_ASSERT_TRUE(or3_1);
  using or3_2 = mpl::or_<mpl::true_, mpl::false_, mpl::false_>;
  STATIC_ASSERT_TRUE(or3_2);
  using or3_3 = mpl::or_<mpl::true_, mpl::false_, mpl::false_>;
  STATIC_ASSERT_TRUE(or3_3);
  using or3_4 = mpl::or_<mpl::false_, mpl::true_, mpl::true_>;
  STATIC_ASSERT_TRUE(or3_4);
  using or3_5 = mpl::or_<mpl::false_, mpl::true_, mpl::false_>;
  STATIC_ASSERT_TRUE(or3_5);
  using or3_6 = mpl::or_<mpl::false_, mpl::false_, mpl::true_>;
  STATIC_ASSERT_TRUE(or3_6);
  using or3_7 = mpl::or_<mpl::true_, mpl::true_, mpl::true_>;
  STATIC_ASSERT_TRUE(or3_7);
}

TEST(or_test, false_)
{
  namespace mpl = nek::mpl;
  using or1 = mpl::or_<mpl::false_>;
  STATIC_ASSERT_FALSE(or1);
  using or2 = mpl::or_<mpl::false_, mpl::false_>;
  STATIC_ASSERT_FALSE(or2);
  using or3 = mpl::or_<mpl::false_, mpl::false_, mpl::false_>;
  STATIC_ASSERT_FALSE(or3);
  using or4 = mpl::or_<mpl::false_, mpl::false_, mpl::false_>;
  STATIC_ASSERT_FALSE(or4);
}
