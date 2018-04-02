#include <nek/mpl/integral_c.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"

template <class T>
class integral_c_test
    : public ::testing::Test
{
};

using types = ::testing::Types<
    char,
    short,
    int,
    long
>;

TYPED_TEST_CASE(integral_c_test, types);

TYPED_TEST(integral_c_test, member)
{
    using integral = nek::mpl::integral_c<TypeParam, 0>;
    STATIC_ASSERT_EQ(typename integral::value_type, TypeParam);
    STATIC_ASSERT_EQ(typename integral::type, integral);
    STATIC_ASSERT_EQ(typename integral::tag, nek::mpl::integral_c_tag);
    EXPECT_EQ(0, static_cast<TypeParam>(integral::value));
    using next_type = nek::mpl::integral_c<TypeParam, 1>;
    STATIC_ASSERT_EQ(typename integral::next, next_type);
    using prior_type = nek::mpl::integral_c<TypeParam, -1>;
    STATIC_ASSERT_EQ(typename integral::prior, prior_type);
    SUCCEED();
}
