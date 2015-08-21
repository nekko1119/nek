#include <nek/mpl/not.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"

TEST(not_c, true)
{
    namespace mpl = nek::mpl;
    STATIC_ASSERT_TRUE_VALUE(mpl::not_c<false>);
}

TEST(not_c, false)
{
    namespace mpl = nek::mpl;
    STATIC_ASSERT_FALSE_VALUE(mpl::not_c<true>);
}

TEST(not_, true_)
{
    namespace mpl = nek::mpl;
    STATIC_ASSERT_TRUE_VALUE(mpl::not_<mpl::false_>);
}

TEST(not_, false_)
{
    namespace mpl = nek::mpl;
    STATIC_ASSERT_FALSE_VALUE(mpl::not_<mpl::true_>);
}