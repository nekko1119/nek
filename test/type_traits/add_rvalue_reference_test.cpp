#include <nek/type_traits/add_rvalue_reference.hpp>
#include <gtest/gtest.h>
#include "static_assert.hpp"

TEST(add_rvalue_reference_test, normal)
{
  // non-spec, lref, rref
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int>::type, int&&);
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int&>::type, int&);
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int&&>::type, int&&);

  // cv-spec, lref, rref
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int const>::type, int const&&);
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int volatile>::type, int volatile&&);
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int const volatile>::type, int const volatile&&);

  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int const&>::type, int const&);
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int volatile&>::type, int volatile&);
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int const volatile&>::type, int const volatile&);

  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int const&&>::type, int const&&);
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int volatile&&>::type, int volatile&&);
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int const volatile&&>::type, int const volatile&&);

  // void
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<void>::type, void);
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<void const>::type, void const);
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<void volatile>::type, void volatile);
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<void const volatile>::type, void const volatile);

  // others
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int*>::type, int*&&);
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<int []>::type, int (&&)[]);
  STATIC_ASSERT_EQ(nek::add_rvalue_reference<void ()>::type, void (&&)());

}