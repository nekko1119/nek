#include <nek\allocator\allocator.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"

TEST(allocator_test, member_type)
{
  using type = nek::allocator<int>;
  STATIC_ASSERT_EQ(type::value_type, int);
  STATIC_ASSERT_EQ(type::reference, int&);
  STATIC_ASSERT_EQ(type::const_reference, int const&);
  STATIC_ASSERT_EQ(type::pointer, int*);
  STATIC_ASSERT_EQ(type::const_pointer, int const*);
  STATIC_ASSERT_EQ(type::difference_type, std::ptrdiff_t);
  STATIC_ASSERT_EQ(type::size_type, std::size_t);
  STATIC_ASSERT_EQ(type::rebind<double>::other, nek::allocator<double>);
}