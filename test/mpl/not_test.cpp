#include <nek/mpl/not.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"

TEST(not_c, true)
{
    namespace mpl = nek::mpl;
    STATIC_ASSERT_TRUE(mpl::not_c<false>);
}

TEST(not_c, false)
{
    namespace mpl = nek::mpl;
    STATIC_ASSERT_FALSE(mpl::not_c<true>);
}

TEST(not_, true_)
{
    namespace mpl = nek::mpl;
    STATIC_ASSERT_TRUE(mpl::not_<mpl::false_>);
}

TEST(not_, false_)
{
    namespace mpl = nek::mpl;
    STATIC_ASSERT_FALSE(mpl::not_<mpl::true_>);
}