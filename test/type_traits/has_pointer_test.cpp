#include <nek/type_traits/has_pointer.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

#define NEK_MEMBER_TYPE pointer
#include "has_member_type.hpp"
#undef NEK_MEMBER_TYPE

TEST(has_pointer_test, initialize_true)
{
    STATIC_ASSERT_TRUE(nek::has_pointer<has_member_type>);
    STATIC_ASSERT_EQ(nek::has_pointer<has_member_type>::type, nek::true_type);
    STATIC_ASSERT_EQ(nek::has_pointer<has_member_type>::value_type, bool);
    EXPECT_EQ(true, nek::has_pointer<has_member_type>());
    SUCCEED();
}

TEST(has_pointer_test, initialize_false)
{
    STATIC_ASSERT_FALSE(nek::has_pointer<int>);
    STATIC_ASSERT_EQ(nek::has_pointer<int>::type, nek::false_type);
    STATIC_ASSERT_EQ(nek::has_pointer<int>::value_type, bool);
    EXPECT_EQ(false, nek::has_pointer<int>());
    SUCCEED();
}

TEST(has_pointer_test, normal)
{
    NEK_HAS_MEMBER_TYPE(nek::has_pointer);
    SUCCEED();
}