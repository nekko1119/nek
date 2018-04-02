#ifndef NEK_TYPE_TRAITS_TEST_STATIC_ASSERT_HPP
#define NEK_TYPE_TRAITS_TEST_STATIC_ASSERT_HPP

#include <type_traits>
#include <gtest/gtest.h>
#include <nek/type_traits/integral_constant.hpp>

// these macros are in order to use static assert more easier.
#define STATIC_ASSERT_TRUE_VALUE(pred)\
    static_assert(pred::value, #pred "::value == true")

#define STATIC_ASSERT_TRUE(value)\
    static_assert(value, #value " == true")

#define STATIC_ASSERT_FALSE_VALUE(pred)\
    static_assert(! pred::value, #pred "::value == false")

#define STATIC_ASSERT_FALSE(value)\
    static_assert(! value, #value " == false")

#define STATIC_ASSERT_EQ(actual_type, expect_type)\
    static_assert(std::is_same<actual_type, expect_type>::value, "std::is_same<" #actual_type ", " #expect_type ">::value")

#define STATIC_ASSERT_NE(actual_type, expect_type)\
    static_assert(!std::is_same<actual_type, expect_type>::value, "std::is_same<" #actual_type ", " #expect_type ">::value")

namespace nektest
{
    template <class T>
    inline void require_true_type_member()
    {
        STATIC_ASSERT_TRUE_VALUE(T);
        STATIC_ASSERT_EQ(typename T::type, nek::true_type);
        STATIC_ASSERT_EQ(typename T::value_type, bool);
        STATIC_ASSERT_TRUE(T{});
        STATIC_ASSERT_TRUE(static_cast<bool>(T{}));
        STATIC_ASSERT_TRUE(T{}());
    }

    template <class T>
    inline void require_false_type_member()
    {
        STATIC_ASSERT_FALSE_VALUE(T);
        STATIC_ASSERT_EQ(typename T::type, nek::false_type);
        STATIC_ASSERT_EQ(typename T::value_type, bool);
        STATIC_ASSERT_FALSE(T{});
        STATIC_ASSERT_FALSE(static_cast<bool>(T{}));
        STATIC_ASSERT_FALSE(T{}());
    }
}
#endif
