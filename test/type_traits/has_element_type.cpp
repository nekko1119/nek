#include <nek/type_traits/has_element_type.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

#define NEK_MEMBER_TYPE element_type
#include "has_member_type.hpp"
#undef NEK_MEMBER_TYPE

TEST(has_element_type_test, initialize_true)
{
    nektest::require_true_type_member<nek::has_element_type<has_member_type>>();
}

TEST(has_element_type_test, initialize_false)
{
    nektest::require_false_type_member<nek::has_element_type<int>>();
}

TEST(has_element_type_test, normal)
{
    NEK_HAS_MEMBER_TYPE(nek::has_element_type);
    SUCCEED();
}
