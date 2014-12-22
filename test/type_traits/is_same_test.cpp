#include <nek/type_traits/is_same.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(is_same_test, initialize_true)
{
    nektest::require_true_type_member<nek::is_same<int, int>>();
}

TEST(is_same_test, initialize_false)
{
    nektest::require_false_type_member<nek::is_same<int, double>>();
}

TEST(is_same_test, yes)
{
    using value_type = nek::is_same<int, int>;
    using lref_type = nek::is_same<int&, int&>;
    using rref_type = nek::is_same<int&&, int&&>;
    using arr_type = nek::is_same<int[], int[]>;
    using arr_type2 = nek::is_same<int[2], int[2]>;
    using func_type = nek::is_same<void(), void()>;

    STATIC_ASSERT_TRUE(value_type);
    STATIC_ASSERT_TRUE(lref_type);
    STATIC_ASSERT_TRUE(rref_type);
    STATIC_ASSERT_TRUE(arr_type);
    STATIC_ASSERT_TRUE(arr_type2);
    STATIC_ASSERT_TRUE(func_type);
}

TEST(is_same_test, no)
{
    using const_type = nek::is_same<int, int const>;
    using lref_type = nek::is_same<int, int&>;
    using rref_type = nek::is_same<int, int&&>;
    using arr_type = nek::is_same<int[], int[2]>;
    using arr_type2 = nek::is_same<int(*)[2], int(&)[2]>;
    using cptr_type = nek::is_same<int*, int const>;
    using ptrc_type = nek::is_same <int*, int* const>;

    STATIC_ASSERT_FALSE(const_type);
    STATIC_ASSERT_FALSE(lref_type);
    STATIC_ASSERT_FALSE(rref_type);
    STATIC_ASSERT_FALSE(arr_type);
    STATIC_ASSERT_FALSE(arr_type2);
    STATIC_ASSERT_FALSE(cptr_type);
    STATIC_ASSERT_FALSE(ptrc_type);
}