#include <nek/container/vector.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include "../type_traits/static_assert.hpp"

namespace
{
  template <class T>
  struct min_state_allocator
  {
    using value_type = T;

    int n;
    min_state_allocator()
      : n{0}
    {
    }

    min_state_allocator(int n)
      : n{n}
    {
    }

    template <class U>
    min_state_allocator(min_state_allocator<U> const&)
    {
    }

    T* allocate(std::size_t count)
    {
      return new T[count];
    }

    void deallocate(T* p, std::size_t)
    {
      delete[] p;
    }
  };

  template <class T, class U>
  bool operator==(min_state_allocator<T> const& l, min_state_allocator<U> const& r)
  {
    return l.n == r.n;
  }

  template <class T, class U>
  bool operator!=(min_state_allocator<T> const& l, min_state_allocator<U> const& r)
  {
    return !(l == r);
  }
}

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

TEST_F(vector_test, default_constructor)
{
  nek::vector<int> instance;
  nek::allocator<int> alloc;
  EXPECT_EQ(alloc, instance.get_allocator());
  EXPECT_TRUE(nek::is_empty(instance));
  EXPECT_GE(instance.capacity(), nek::size(instance));
}

TEST_F(vector_test, sized_constructor)
{
  constexpr std::size_t size = 4U;
  nek::allocator<int> alloc;
  nek::vector<int> instance(size);
  EXPECT_EQ(alloc, instance.get_allocator());
  EXPECT_EQ(size, nek::size(instance));
  EXPECT_GE(instance.capacity(), nek::size(instance));
}

TEST_F(vector_test, get_allocator)
{
  min_state_allocator<int> alloc{42};
  nek::vector<int, min_state_allocator<int>> v{alloc};
  min_state_allocator<int> actual = v.get_allocator();
  EXPECT_EQ(alloc, actual);
  EXPECT_NE(&alloc, &actual);
}

TEST_F(vector_test, reserve)
{
  nek::vector<int> v{4};
  v[2] = 42;
  ASSERT_LE(4U, v.capacity());
  v.reserve(5);
  EXPECT_EQ(5, v.capacity());
  v.reserve(1);
  EXPECT_EQ(5, v.capacity());
  EXPECT_THROW(v.reserve((unsigned)-1), std::length_error);
  v.reserve(7);
  EXPECT_EQ(7, v.capacity());
  EXPECT_EQ(42, v[2]);
}

TEST_F(vector_test, subscript)
{
  constexpr std::size_t size = 4U;
  nek::vector<int> v(size);
  v[0] = 11;
  v[1] = 22;
  v[2] = 33;
  v[3] = 44;
  EXPECT_EQ(11, v[0]);
  EXPECT_EQ(22, v[1]);
  EXPECT_EQ(33, v[2]);
  EXPECT_EQ(44, v[3]);
}

TEST_F(vector_test, emplace_back)
{
  // setup
  sut.reserve(2);

  sut.emplace_back(13);
  EXPECT_EQ(1, nek::size(sut));
  EXPECT_LE(2U, sut.capacity());
  EXPECT_EQ(13, sut[0]);

  sut.emplace_back(17);
  sut.emplace_back(19);
  sut.emplace_back(23);
  sut.emplace_back(29);
  EXPECT_LE(5U, sut.capacity());
  EXPECT_EQ(5, nek::size(sut));
  EXPECT_EQ(17, sut[1]);
  EXPECT_EQ(19, sut[2]);
  EXPECT_EQ(23, sut[3]);
  EXPECT_EQ(29, sut[4]);
}