#include <nek/type_traits/is_class.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_class_test, initialize_true)
{
    using namespace type_traits_test;
    nektest::require_true_type_member<nek::is_class<class_type>>();
}

TEST(is_class_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_class<int>>();
}

TEST(is_class_test, yes)
{
    using namespace type_traits_test;
    STATIC_ASSERT_TRUE_VALUE(nek::is_class<class_type>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_class<class_type const>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_class<class_type volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_class<class_type const volatile>);
    SUCCEED();
}

TEST(is_class_test, no)
{
    using namespace type_traits_test;
    STATIC_ASSERT_FALSE_VALUE(nek::is_class<int>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_class<void>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_class<class_type*>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_class<class_type[]>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_class<class_type&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_class<class_type&&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_class<enum_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_class<union_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_class<f1_type>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_class<mf1_type>);
    SUCCEED();
}
