#include <nek/iterator/iterator.hpp>
#include <iterator>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"

namespace
{
    struct test_iterator
        : public nek::iterator<std::random_access_iterator_tag, int>
    {
    };
}

TEST(iterator_test, member_type)
{
    STATIC_ASSERT_EQ(std::random_access_iterator_tag, test_iterator::iterator_category);
    STATIC_ASSERT_EQ(int, test_iterator::value_type);
    STATIC_ASSERT_EQ(std::ptrdiff_t, test_iterator::difference_type);
    STATIC_ASSERT_EQ(int*, test_iterator::pointer);
    STATIC_ASSERT_EQ(int&, test_iterator::reference);
}
