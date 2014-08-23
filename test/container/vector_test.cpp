#include <nek/container/vector.hpp>
#include <nek/iterator/range.hpp>
#include <gtest/gtest.h>
#include <cstddef>
#include <list>
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
  STATIC_ASSERT_EQ(type::reverse_iterator, nek::reverse_iterator<type::iterator>);
  STATIC_ASSERT_EQ(type::const_reverse_iterator, nek::reverse_iterator<type::const_iterator>);
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

TEST_F(vector_test, range_constructor)
{
  std::list<int> original = {1, 2, 3};
  nek::vector<int> instance{original.begin(), original.end()};
  EXPECT_EQ(3, nek::size(instance));
  EXPECT_EQ(1, instance[0]);
  EXPECT_EQ(2, instance[1]);
  EXPECT_EQ(3, instance[2]);
}

TEST_F(vector_test, initializer_list_constructor)
{
  nek::vector<int> instance = {1, 2, 3};
  EXPECT_EQ(3, nek::size(instance));
  EXPECT_EQ(1, instance[0]);
  EXPECT_EQ(2, instance[1]);
  EXPECT_EQ(3, instance[2]);
}

TEST_F(vector_test, copy_constructor)
{
  nek::emplace_back(sut, 0);
  nek::emplace_back(sut, 1);
  nek::emplace_back(sut, 2);
  nek::vector<int> copied{sut};
  EXPECT_EQ(nek::size(sut), size(copied));
  EXPECT_EQ(0, copied[0]);
  EXPECT_EQ(1, copied[1]);
  EXPECT_EQ(2, copied[2]);
  EXPECT_NE(sut.begin(), copied.begin());
}

TEST_F(vector_test, move_constructor)
{
  nek::emplace_back(sut, 0);
  nek::emplace_back(sut, 1);
  nek::emplace_back(sut, 2);
  nek::vector<int> moved = nek::move(sut);
  EXPECT_EQ(3, nek::size(moved));
  EXPECT_EQ(0, moved[0]);
  EXPECT_EQ(1, moved[1]);
  EXPECT_EQ(2, moved[2]);
}

TEST_F(vector_test, swap)
{
  nek::emplace_back(sut, 1);
  nek::emplace_back(sut, 2);
  nek::emplace_back(sut, 3);
  nek::vector<int> other;
  nek::emplace_back(other, 10);
  nek::emplace_back(other, 20);

  sut.swap(other);
  EXPECT_EQ(nek::size(sut), 2);
  EXPECT_EQ(nek::size(other), 3);
  EXPECT_EQ(sut[0], 10);
  EXPECT_EQ(other[0], 1);
}

TEST_F(vector_test, get_allocator)
{
  min_state_allocator<int> alloc{42};
  nek::vector<int, min_state_allocator<int>> v{alloc};
  min_state_allocator<int> actual = v.get_allocator();
  EXPECT_EQ(alloc, actual);
  EXPECT_NE(&alloc, &actual);
}

TEST_F(vector_test, max_size)
{
  nek::allocator<int> alloc;
  nek::vector<int, nek::allocator<int>> v(alloc);
  EXPECT_EQ(alloc.max_size(), v.max_size());
}

TEST_F(vector_test, data)
{
  emplace_back(sut, 1);
  emplace_back(sut, 2);
  emplace_back(sut, 3);
  int const* p = sut.data();
  EXPECT_EQ(&sut[0], &p[0]);
  EXPECT_EQ(1, sut[0]);
  EXPECT_EQ(2, sut[1]);
  EXPECT_EQ(3, sut[2]);
}

TEST_F(vector_test, reserve)
{
  nek::vector<int> v(4);
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

TEST_F(vector_test, iterator)
{
  nek::vector<int> const v = {1, 2, 3, 4};
  int expected[] = {1, 2, 3, 4};
  int index = 0;
  for (auto it = v.begin(); it != v.end(); ++it) {
    EXPECT_EQ(expected[index++], *it);
  }
}

TEST_F(vector_test, reverse_iterator)
{
  nek::vector<int> const v = {1, 2, 3, 4};
  int expected[] = {4, 3, 2, 1};
  int index = 0;
  for (auto it = nek::rbegin(v); it != nek::rend(v); ++it) {
    EXPECT_EQ(expected[index++], *it);
  }
}

TEST_F(vector_test, subscript)
{
  constexpr std::size_t size = 4U;
  nek::vector<int> v(size);
  ASSERT_EQ(4,nek::size(v));
  v[0] = 11;
  v[1] = 22;
  v[2] = 33;
  v[3] = 44;
  EXPECT_EQ(11, v[0]);
  EXPECT_EQ(22, v[1]);
  EXPECT_EQ(33, v[2]);
  EXPECT_EQ(44, v[3]);
}

TEST_F(vector_test, insert)
{
  nek::vector<int> v = {1, 2, 3};
  int a[] = {10, 20, 30};
  v.insert(v.begin() + 1, a, a + 3);
  EXPECT_EQ(6, nek::size(v));
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(10, v[1]);
  EXPECT_EQ(20, v[2]);
  EXPECT_EQ(30, v[3]);
  EXPECT_EQ(2, v[4]);
  EXPECT_EQ(3, v[5]);
  EXPECT_THROW(v.insert(v.begin(), a, a + v.max_size()), std::length_error);
}

TEST_F(vector_test, emplace)
{
  // setup
  sut.reserve(2);

  sut.emplace(sut.end(), 13);
  EXPECT_EQ(1, nek::size(sut));
  EXPECT_LE(2U, sut.capacity());
  EXPECT_EQ(13, sut[0]);

  sut.emplace(sut.end(), 17);
  sut.emplace(sut.end(), 19);
  sut.emplace(sut.begin(), 23);
  sut.emplace(sut.begin(), 29);
  EXPECT_LE(5U, sut.capacity());
  EXPECT_EQ(5, nek::size(sut));
  EXPECT_EQ(29, sut[0]);
  EXPECT_EQ(23, sut[1]);
  EXPECT_EQ(13, sut[2]);
  EXPECT_EQ(17, sut[3]);
  EXPECT_EQ(19, sut[4]);
}

TEST_F(vector_test, erase)
{
  nek::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  v.erase(v.begin() + 1, v.begin() + 7);
  EXPECT_EQ(3, nek::size(v));
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(8, v[1]);
  EXPECT_EQ(9, v[2]);
}

TEST_F(vector_test, at)
{
  nek::emplace_back(sut, 1);
  nek::emplace_back(sut, 2);
  nek::emplace_back(sut, 3);
  EXPECT_EQ(1, nek::at(sut, 0));
  nek::at(sut, 1) = 10;
  EXPECT_EQ(10, sut[1]);
  EXPECT_THROW(nek::at(sut, 4), std::out_of_range);
}

TEST_F(vector_test, emplace_back)
{
  nek::emplace_back(sut, 1);
  nek::emplace_back(sut, 2);
  nek::emplace_back(sut, 3);
}

TEST_F(vector_test, insert_family)
{
  nek::insert(sut, sut.end(), 10);
  EXPECT_EQ(1, nek::size(sut));
  EXPECT_EQ(10, sut[0]);

  int n = 20;
  nek::insert(sut, sut.end(), n);
  EXPECT_EQ(2, nek::size(sut));
  EXPECT_EQ(10, sut[0]);
  EXPECT_EQ(20, sut[1]);

  nek::insert(sut, sut.end(), 3, 30);
  EXPECT_EQ(5, nek::size(sut));
  EXPECT_EQ(10, sut[0]);
  EXPECT_EQ(20, sut[1]);
  EXPECT_EQ(30, sut[2]);
  EXPECT_EQ(30, sut[3]);
  EXPECT_EQ(30, sut[4]);

  nek::insert(sut, sut.end(), {40, 50, 60});
  EXPECT_EQ(8, nek::size(sut));
  EXPECT_EQ(10, sut[0]);
  EXPECT_EQ(20, sut[1]);
  EXPECT_EQ(30, sut[2]);
  EXPECT_EQ(30, sut[3]);
  EXPECT_EQ(30, sut[4]);
  EXPECT_EQ(40, sut[5]);
  EXPECT_EQ(50, sut[6]);
  EXPECT_EQ(60, sut[7]);
}

TEST_F(vector_test, insert_family_reserve_enough_size)
{
  sut.reserve(64);
  nek::insert(sut, sut.end(), 10);
  EXPECT_EQ(1, nek::size(sut));
  EXPECT_EQ(10, sut[0]);

  int n = 20;
  nek::insert(sut, sut.end(), n);
  EXPECT_EQ(2, nek::size(sut));
  EXPECT_EQ(10, sut[0]);
  EXPECT_EQ(20, sut[1]);

  nek::insert(sut, sut.end(), 3, 30);
  EXPECT_EQ(5, nek::size(sut));
  EXPECT_EQ(10, sut[0]);
  EXPECT_EQ(20, sut[1]);
  EXPECT_EQ(30, sut[2]);
  EXPECT_EQ(30, sut[3]);
  EXPECT_EQ(30, sut[4]);

  nek::insert(sut, sut.end(), {40, 50, 60});
  EXPECT_EQ(8, nek::size(sut));
  EXPECT_EQ(10, sut[0]);
  EXPECT_EQ(20, sut[1]);
  EXPECT_EQ(30, sut[2]);
  EXPECT_EQ(30, sut[3]);
  EXPECT_EQ(30, sut[4]);
  EXPECT_EQ(40, sut[5]);
  EXPECT_EQ(50, sut[6]);
  EXPECT_EQ(60, sut[7]);
}

TEST_F(vector_test, pop_back)
{
  nek::vector<int> v = {1, 2, 3};
  nek::pop_back(v);
  EXPECT_EQ(2, nek::size(v));
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
}

TEST_F(vector_test, push_back)
{
  nek::push_back(sut, 1);
  int a = 2;
  nek::push_back(sut, 2);
  EXPECT_EQ(1, sut[0]);
  EXPECT_EQ(2, sut[1]);
}

TEST_F(vector_test, front)
{
  nek::push_back(sut, 1);
  nek::push_back(sut, 2);
  EXPECT_EQ(1, nek::front(sut));
}

TEST_F(vector_test, clear)
{
  nek::push_back(sut, 1);
  nek::push_back(sut, 2);
  nek::push_back(sut, 3);
  nek::clear(sut);
  EXPECT_TRUE(nek::is_empty(sut));
}
