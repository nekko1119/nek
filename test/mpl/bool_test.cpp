#include <nek/mpl/bool.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"

TEST(bool_test, member)
{
    using true_t = nek::mpl::bool_<true>;
    STATIC_ASSERT_EQ(typename true_t::value_type, bool);
    STATIC_ASSERT_EQ(typename true_t::type, true_t);
    STATIC_ASSERT_EQ(typename true_t::tag, nek::mpl::integral_c_tag);
    STATIC_ASSERT_TRUE_VALUE(true_t);
    STATIC_ASSERT_TRUE(true_t{});
    STATIC_ASSERT_TRUE(static_cast<bool>(true_t{}));
    STATIC_ASSERT_TRUE(true_t{}());

    using false_t = nek::mpl::bool_<false>;
    STATIC_ASSERT_EQ(typename false_t::value_type, bool);
    STATIC_ASSERT_EQ(typename false_t::type, false_t);
    STATIC_ASSERT_EQ(typename false_t::tag, nek::mpl::integral_c_tag);
    STATIC_ASSERT_FALSE_VALUE(false_t);
    STATIC_ASSERT_FALSE(false_t{});
    STATIC_ASSERT_FALSE(static_cast<bool>(false_t{}));
    STATIC_ASSERT_FALSE(false_t{}());

    SUCCEED();
}