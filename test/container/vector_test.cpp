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
  EXPECT_EQ(0, instance.size());
}

TEST_F(vector_test, resize_constructor)
{
  std::size_t size = 4U;
  nek::allocator<int> alloc;
  nek::vector<int> instance{size};
  EXPECT_EQ(alloc, instance.get_allocator());
  EXPECT_EQ(size, instance.size());
}

TEST_F(vector_test, get_allocator)
{
  min_state_allocator<int> alloc{42};
  nek::vector<int, min_state_allocator<int>> v{alloc};
  min_state_allocator<int> actual = v.get_allocator();
  EXPECT_EQ(alloc, actual);
  EXPECT_NE(&alloc, &actual);
}