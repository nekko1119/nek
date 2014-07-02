#include <nek/allocator/allocator_traits.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"
#include <nek/allocator/allocator.hpp>

TEST(allocator_traits_test, allocator_member_type)
{
  using type = nek::allocator_traits<nek::allocator<int>>;
  STATIC_ASSERT_EQ(type::allocator_type, nek::allocator<int>);
  STATIC_ASSERT_EQ(type::value_type, int);
  STATIC_ASSERT_EQ(type::pointer, int*);
  STATIC_ASSERT_EQ(type::const_pointer, int const*);
  STATIC_ASSERT_EQ(type::void_pointer, void*);
  STATIC_ASSERT_EQ(type::const_void_pointer, void const*);
  STATIC_ASSERT_EQ(type::difference_type, std::ptrdiff_t);
  STATIC_ASSERT_EQ(type::size_type, std::size_t);
  STATIC_ASSERT_EQ(type::propagate_on_container_copy_assignment, nek::false_type);
  STATIC_ASSERT_EQ(type::propagate_on_container_move_assignment, nek::false_type);
  STATIC_ASSERT_EQ(type::propagate_on_container_swap, nek::false_type);
}