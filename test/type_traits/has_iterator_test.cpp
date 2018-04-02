#include <nek/type_traits/has_iterator.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

#define NEK_MEMBER_TYPE iterator
#include "has_member_type.hpp"
#undef NEK_MEMBER_TYPE

TEST(has_iterator_test, initialize_true)
{
    nektest::require_true_type_member<nek::has_iterator<has_member_type>>();
}

TEST(has_iterator_test, initialize_false)
{
    nektest::require_false_type_member<nek::has_iterator<int>>();
}

TEST(has_iterator_test, normal)
{
    NEK_HAS_MEMBER_TYPE(nek::has_iterator);
    SUCCEED();
}
