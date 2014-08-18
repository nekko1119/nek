#include <nek/iterator/normal_iterator.hpp>
#include <gtest/gtest.h>
#include <initializer_list>
#include <string>
#include <vector>
#include "../type_traits/static_assert.hpp"

class normal_iterator_test
  : public ::testing::Test
{
protected:
  using mock_type = std::vector<std::string>;
  using iter_type = mock_type::iterator;
  using type = nek::normal_iterator<iter_type>;

  mock_type mock;
  type sut;

  normal_iterator_test()
    : mock{{"this", "is", "a", "test"}},
    sut{mock.begin()}
  {
  }
};

TEST_F(normal_iterator_test, member_type)
{
  STATIC_ASSERT_EQ(type::value_type, std::string);
  STATIC_ASSERT_EQ(type::iterator_type, iter_type);
  STATIC_ASSERT_EQ(type::iterator_category, std::random_access_iterator_tag);
  STATIC_ASSERT_EQ(type::pointer, mock_type::pointer);
  STATIC_ASSERT_EQ(type::difference_type, std::ptrdiff_t);
  STATIC_ASSERT_EQ(type::reference, std::string&);
}

TEST_F(normal_iterator_test, default_constructor)
{
  nek::normal_iterator<iter_type> instance;
}

TEST_F(normal_iterator_test, assign_constructor)
{
  nek::normal_iterator<iter_type> instance{mock.begin()};
  EXPECT_EQ(mock.begin(), instance.base());
  EXPECT_EQ(*mock.begin(), *instance);
}

TEST_F(normal_iterator_test, base)
{
  EXPECT_EQ(mock.begin(), sut.base());
}

TEST_F(normal_iterator_test, dereference)
{
  EXPECT_EQ(*mock.begin(), *sut);
}

TEST_F(normal_iterator_test, arrow)
{
  EXPECT_EQ(mock.begin()->length(), sut->length());
}

TEST_F(normal_iterator_test, prefix_increment)
{
  ++sut;
  auto expected = ++mock.begin();
  EXPECT_EQ(*expected, *sut);
}

TEST_F(normal_iterator_test, suffix_increment)
{
  auto actual = sut++;
  auto expected = ++mock.begin();
  EXPECT_EQ(*mock.begin(), *actual);
  EXPECT_EQ(*expected, *sut);
}

TEST_F(normal_iterator_test, prefix_decrement)
{
  type end{mock.end()};
  --end;
  auto expected = --mock.end();
  EXPECT_EQ(*expected, *end);
}

TEST_F(normal_iterator_test, suffix_decrement)
{
  type end{mock.end()};
  auto actual = end--;
  auto expected = --mock.end();
  EXPECT_EQ(mock.end(), actual.base());
  EXPECT_EQ(*expected, *end);
}

TEST_F(normal_iterator_test, subscript)
{
  EXPECT_EQ(sut[2], mock[2]);
}

TEST_F(normal_iterator_test, plus)
{
  auto actual1 = sut + 2;
  auto actual2 = 2 + sut;
  sut += 2;
  auto expected = mock.begin() + 2;
  EXPECT_EQ(expected, actual1.base());
  EXPECT_EQ(expected, actual2.base());
  EXPECT_EQ(expected, sut.base());
}

TEST_F(normal_iterator_test, minus)
{
  type end{mock.end()};
  auto actual = end - 2;
  end -= 2;
  auto expected = mock.end() - 2;
  EXPECT_EQ(expected, actual.base());
  EXPECT_EQ(expected, end.base());
}


TEST_F(normal_iterator_test, compare)
{
  nek::normal_iterator<iter_type> begin{mock.begin()};
  nek::normal_iterator<iter_type> end{mock.end()};
  EXPECT_LT(begin, end);
  EXPECT_LE(begin, end);
  EXPECT_GT(end, begin);
  EXPECT_GE(end, begin);
}

TEST_F(normal_iterator_test, equal)
{
  nek::normal_iterator<iter_type> begin{mock.begin()};
  nek::normal_iterator<iter_type> end{mock.end()};
  EXPECT_EQ(begin, begin);
  EXPECT_NE(begin, end);
}
