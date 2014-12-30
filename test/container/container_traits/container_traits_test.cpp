#include <nek/container/container_traits.hpp>
#include <gtest/gtest.h>
#include <nek/container/vector.hpp>
#include "test/type_traits/static_assert.hpp"

TEST(container_traits_test, nek_container)
{
    using type = nek::vector<int>;
    STATIC_ASSERT_EQ(type::value_type, nek::container_traits::value_type_t<type>);
    STATIC_ASSERT_EQ(type::size_type, nek::container_traits::size_type_t<type>);
    STATIC_ASSERT_EQ(nek::container_traits::nek_container_tag, nek::container_traits::container_tag_t<type>);
}

TEST(container_traints_test, array)
{
    using type = int[];
    STATIC_ASSERT_EQ(int, nek::container_traits::value_type_t<type>);
    STATIC_ASSERT_EQ(std::size_t, nek::container_traits::size_type_t<type>);
    STATIC_ASSERT_EQ(nek::container_traits::array_container_tag, nek::container_traits::container_tag_t<type>);
}