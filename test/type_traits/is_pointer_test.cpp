#include <nek/type_traits/is_pointer.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"
#include "test_type.hpp"

TEST(is_pointer_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_pointer<int*>>();
}

TEST(is_pointer_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_pointer<int>>();
}

TEST(is_pointer_test, yes)
{
    using namespace type_traits_test;
    STATIC_ASSERT_TRUE_VALUE(nek::is_pointer<int*>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_pointer<int**>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_pointer<int const*>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_pointer<int volatile*>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_pointer<int const volatile*>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_pointer<int* const>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_pointer<int* volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_pointer<int* const volatile>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_pointer<f1_type>);
    STATIC_ASSERT_TRUE_VALUE(nek::is_pointer<int(*)[]>);
    SUCCEED();
}

TEST(is_pointer_test, no)
{
    using namespace type_traits_test;
    STATIC_ASSERT_FALSE_VALUE(nek::is_pointer<int>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_pointer<void>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_pointer<std::nullptr_t>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_pointer<int&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_pointer<int&&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_pointer<int[]>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_pointer<int(&)[]>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_pointer<void()>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_pointer<void(&)()>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_pointer<int*&>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_pointer<int(&)[]>);
    STATIC_ASSERT_FALSE_VALUE(nek::is_pointer<mf1_type>);

    SUCCEED();
}
