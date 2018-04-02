#include <nek/type_traits/is_enum.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

namespace
{
    enum class scoped_enum_type
    {
        a,
        b,
        c
    };
}

TEST(is_enum_test, initialize_true)
{
    using namespace type_traits_test;
    nektest::require_true_type_member<nek::is_enum<enum_type>>();
}

TEST(is_enum_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_enum<int>>();
}

TEST(is_enum_test, yes)
{
    using namespace type_traits_test;
    STATIC_ASSERT_TRUE_VALUE(nek::is_enum<enum_type>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_enum<enum_type const>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_enum<enum_type volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_enum<enum_type const volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_enum<scoped_enum_type>);
    SUCCEED();
}

TEST(is_enum_test, no)
{
    using namespace type_traits_test;
    STATIC_ASSERT_FALSE_VALUE(nek::is_enum<int>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_enum<void>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_enum<enum_type*>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_enum<enum_type[]>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_enum<enum_type&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_enum<enum_type&&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_enum<class_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_enum<union_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_enum<f1_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_enum<mf1_type>);
    SUCCEED();
}
