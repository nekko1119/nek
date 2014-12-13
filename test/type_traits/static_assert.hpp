#ifndef NEK_TYPE_TRAITS_TEST_STATIC_ASSERT_HPP
#define NEK_TYPE_TRAITS_TEST_STATIC_ASSERT_HPP

#include <type_traits>

// these macros are in order to use static assert more easier.
#define STATIC_ASSERT_TRUE(pred)\
    static_assert(pred::value, #pred "::value == true")

#define STATIC_ASSERT_FALSE(pred)\
    static_assert(!pred::value, #pred "::value == false")

#define STATIC_ASSERT_EQ(actual_type, expect_type)\
    static_assert(std::is_same<actual_type, expect_type>::value, "std::is_same<" #actual_type ", " #expect_type ">::value")

#define STATIC_ASSERT_NE(actual_type, expect_type)\
    static_assert(!std::is_same<actual_type, expect_type>::value, "std::is_same<" #actual_type ", " #expect_type ">::value")

#endif