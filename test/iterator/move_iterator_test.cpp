#include <nek/iterator/move_iterator.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../type_traits/test_type.hpp"
#include "../type_traits/static_assert.hpp"

namespace
{
  struct throwable
  {
    throwable() = default;
    throwable(throwable const&) = default;
    throwable& operator=(throwable const&) = default;
    throwable(throwable&&){}
    throwable& operator=(throwable&&) { return *this; }
  };
}

class move_iterator_test
  : public ::testing::Test
{
protected:
  using mock_type = std::vector<std::string>;
  using iter_type = mock_type::iterator;
  using type = nek::move_iterator<iter_type>;

  mock_type mock;
  type sut;

  move_iterator_test()
    : mock{{"this", "is", "a", "test"}},
    sut{mock.begin()}
  {
  }
};

TEST_F(move_iterator_test, member_type)
{
  STATIC_ASSERT_EQ(type::value_type, std::string);
  STATIC_ASSERT_EQ(type::iterator_type, iter_type);
  STATIC_ASSERT_EQ(type::iterator_category, nek::random_access_iterator_tag);
  STATIC_ASSERT_EQ(type::pointer, iter_type);
  STATIC_ASSERT_EQ(type::difference_type, iter_type::difference_type);
  STATIC_ASSERT_EQ(type::reference, std::string&&);
}

TEST_F(move_iterator_test, default_constructor)
{
  nek::move_iterator<iter_type> instance;
}

TEST_F(move_iterator_test, assign_constructor)
{
  nek::move_iterator<iter_type> instance{mock.begin()};
  EXPECT_EQ(mock.begin(), instance.base());
  EXPECT_EQ(*mock.begin(), *instance);
}

TEST_F(move_iterator_test, base)
{
  EXPECT_EQ(mock.begin(), sut.base());
}

TEST_F(move_iterator_test, dereference)
{
  EXPECT_EQ(*mock.begin(), *sut);
}

TEST_F(move_iterator_test, arrow)
{
  EXPECT_EQ(mock.begin()->length(), sut->length());
}

TEST_F(move_iterator_test, prefix_increment)
{
  ++sut;
  auto expected = ++mock.begin();
  EXPECT_EQ(*expected, *sut);
}

TEST_F(move_iterator_test, suffix_increment)
{
  auto actual = sut++;
  auto expected = ++mock.begin();
  EXPECT_EQ(*mock.begin(), *actual);
  EXPECT_EQ(*expected, *sut);
}

TEST_F(move_iterator_test, prefix_decrement)
{
  type end{mock.end()};
  --end;
  auto expected = --mock.end();
  EXPECT_EQ(*expected, *end);
}

TEST_F(move_iterator_test, suffix_decrement)
{
  type end{mock.end()};
  auto actual = end--;
  auto expected = --mock.end();
  EXPECT_EQ(mock.end(), actual.base());
  EXPECT_EQ(*expected, *end);
}

TEST_F(move_iterator_test, subscript)
{
  EXPECT_EQ(sut[2], mock[2]);
}

TEST_F(move_iterator_test, plus)
{
  auto actual1 = sut + 2;
  auto actual2 = 2 + sut;
  sut += 2;
  auto expected = mock.begin() + 2;
  EXPECT_EQ(expected, actual1.base());
  EXPECT_EQ(expected, actual2.base());
  EXPECT_EQ(expected, sut.base());
}

TEST_F(move_iterator_test, minus)
{
  type end{mock.end()};
  auto actual = end - 2;
  end -= 2;
  auto expected = mock.end() - 2;
  EXPECT_EQ(expected, actual.base());
  EXPECT_EQ(expected, end.base());
}

TEST_F(move_iterator_test, compare)
{
  nek::move_iterator<iter_type> begin{mock.begin()};
  nek::move_iterator<iter_type> end{mock.end()};
  EXPECT_LT(begin, end);
  EXPECT_LE(begin, end);
  EXPECT_GT(end, begin);
  EXPECT_GE(end, begin);
}

TEST_F(move_iterator_test, equal)
{
  nek::move_iterator<iter_type> begin{mock.begin()};
  nek::move_iterator<iter_type> end{mock.end()};
  EXPECT_EQ(begin, begin);
  EXPECT_NE(begin, end);
}

TEST_F(move_iterator_test, make_move_iterator)
{
  auto actual = nek::make_move_iterator(mock.begin());
  EXPECT_EQ(mock.begin(), actual.base());
  EXPECT_EQ(sut, actual);
}

TEST_F(move_iterator_test, make_move_if_noexcept_iterator)
{
  std::vector<throwable> v;
  auto actual = nek::make_if_noexcept_iterator(v.begin());
  STATIC_ASSERT_EQ(decltype(actual), decltype(v)::iterator);

  std::vector<type_traits_test::nothrow_type> v2;
  auto actual2 = nek::make_if_noexcept_iterator(v2.begin());
  using it_type = decltype(v2)::iterator;
  STATIC_ASSERT_EQ(decltype(actual2), nek::move_iterator<it_type>);
}