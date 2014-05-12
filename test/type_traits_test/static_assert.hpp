#ifndef NEK_TYPE_TRAITS_TEST_STATIC_ASSERT_HPP
#define NEK_TYPE_TRAITS_TEST_STATIC_ASSERT_HPP

// this macro is in order to use static assert more easier.
#define STATIC_ASSERT(expression)\
  static_assert(expression, #expression)

#endif