#include <nek/container/vector.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "../type_traits/static_assert.hpp"

class vector_test
  : public ::testing::Test
{
protected:
  using type = nek::vector<int>;
  nek::vector<int> sut;
};

TEST_F(vector_test, member_type)
{
  STATIC_ASSERT_EQ(type::value_type, int);
  STATIC_ASSERT_EQ(type::allocator_type, nek::allocator<int>);
  STATIC_ASSERT_EQ(type::size_type, std::size_t);
  STATIC_ASSERT_EQ(type::difference_type, std::ptrdiff_t);
  STATIC_ASSERT_EQ(type::reference, int&);
  STATIC_ASSERT_EQ(type::const_reference, int const&);
  STATIC_ASSERT_EQ(type::pointer, int*);
  STATIC_ASSERT_EQ(type::const_pointer, int const*);
}