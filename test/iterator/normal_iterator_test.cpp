#include <nek/iterator/normal_iterator.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include "../type_traits/static_assert.hpp"

class normal_iterator_test
  : public ::testing::Test
{
protected:
  using mock_type = std::vector<std::string>;
  using iter_type = mock_type::iterator;
  using type = nek::normal_iterator<iter_type, mock_type>;
};

TEST_F(normal_iterator_test, member_type)
{
  STATIC_ASSERT_EQ(type::value_type, std::string);
  STATIC_ASSERT_EQ(type::iterator_type, iter_type);
  STATIC_ASSERT_EQ(type::iterator_category, std::random_access_iterator_tag);
  STATIC_ASSERT_EQ(type::pointer, iter_type::pointer);
  STATIC_ASSERT_EQ(type::difference_type, iter_type::difference_type);
  STATIC_ASSERT_EQ(type::reference, iter_type::reference);
}