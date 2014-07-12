#include <nek/iterator/move_iterator.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "../type_traits/static_assert.hpp"

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
  STATIC_ASSERT_EQ(type::iterator_category, std::random_access_iterator_tag);
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