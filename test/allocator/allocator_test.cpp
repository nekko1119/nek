﻿#include <nek\allocator\allocator.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"

class allocator_test
  : public ::testing::Test
{
protected:
  nek::allocator<int> sut;
};

TEST_F(allocator_test, member_type)
{
  using type = decltype(sut);
  STATIC_ASSERT_EQ(type::value_type, int);
  STATIC_ASSERT_EQ(type::reference, int&);
  STATIC_ASSERT_EQ(type::const_reference, int const&);
  STATIC_ASSERT_EQ(type::pointer, int*);
  STATIC_ASSERT_EQ(type::const_pointer, int const*);
  STATIC_ASSERT_EQ(type::difference_type, std::ptrdiff_t);
  STATIC_ASSERT_EQ(type::size_type, std::size_t);
  STATIC_ASSERT_EQ(type::rebind<double>::other, nek::allocator<double>);
}

TEST_F(allocator_test, allocate_construct_destroy_deallocate)
{
  int* actual = sut.allocate(3);
  sut.construct(&actual[1], 42);
  EXPECT_EQ(42, actual[1]);
  sut.destroy(actual);
  sut.deallocate(actual, 3);
}

TEST_F(allocator_test, max_size)
{
  EXPECT_EQ(static_cast<unsigned int>(-1) / sizeof(int), sut.max_size());
}

TEST_F(allocator_test, address)
{
  int value = 0;
  EXPECT_EQ(&value, sut.address(value));
}

TEST_F(allocator_test, equal)
{
  EXPECT_TRUE(sut == nek::allocator<double>{});
}

TEST_F(allocator_test, not_equal)
{
  EXPECT_FALSE(sut != nek::allocator<double>{});
}

TEST_F(allocator_test, void_member_type)
{
  using type = nek::allocator<void>;
  STATIC_ASSERT_EQ(type::value_type, void);
  STATIC_ASSERT_EQ(type::pointer, void*);
  STATIC_ASSERT_EQ(type::const_pointer, void const*);
  STATIC_ASSERT_EQ(type::difference_type, std::ptrdiff_t);
  STATIC_ASSERT_EQ(type::size_type, std::size_t);
  STATIC_ASSERT_EQ(type::rebind<double>::other, nek::allocator<double>);
  STATIC_ASSERT_EQ(type::void_pointer, void*);
  STATIC_ASSERT_EQ(type::const_void_pointer, void const*);
}