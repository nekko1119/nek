#include <nek/iterator/iterator_traits.hpp>
#include <nek/iterator/iterator.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"

namespace
{
    struct test_iterator
        : public nek::iterator<std::bidirectional_iterator_tag, int>
    {
    };
}

TEST(iterator_traits_test, iterator)
{
    using type = nek::iterator_traits<test_iterator>;
    STATIC_ASSERT_EQ(type::iterator_category, std::bidirectional_iterator_tag);
    STATIC_ASSERT_EQ(type::value_type, int);
    STATIC_ASSERT_EQ(type::difference_type, std::ptrdiff_t);
    STATIC_ASSERT_EQ(type::pointer, int*);
    STATIC_ASSERT_EQ(type::reference, int&);
}

TEST(iterator_traits_test, pointer)
{
    using type = nek::iterator_traits<int*>;
    STATIC_ASSERT_EQ(type::iterator_category, std::random_access_iterator_tag);
    STATIC_ASSERT_EQ(type::value_type, int);
    STATIC_ASSERT_EQ(type::difference_type, std::ptrdiff_t);
    STATIC_ASSERT_EQ(type::pointer, int*);
    STATIC_ASSERT_EQ(type::reference, int&);
}

TEST(iterator_traits_test, const_pointer)
{
    using type = nek::iterator_traits<int const*>;
    STATIC_ASSERT_EQ(type::iterator_category, std::random_access_iterator_tag);
    STATIC_ASSERT_EQ(type::value_type, int);
    STATIC_ASSERT_EQ(type::difference_type, std::ptrdiff_t);
    STATIC_ASSERT_EQ(type::pointer, int const*);
    STATIC_ASSERT_EQ(type::reference, int const&);
}