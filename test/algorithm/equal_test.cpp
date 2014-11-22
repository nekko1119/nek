#include <nek/algorithm/equal.hpp>
#include <gtest/gtest.h>
#include <list>

TEST(equal_test, cstring_true)
{
    char const* a = "abc";
    char const* b = "abc";
    bool const result = nek::equal(a, a + 3, b);
    EXPECT_TRUE(result);
}

TEST(equal_test, cstring_false)
{
    char const* a = "abc";
    char const* b = "abd";
    bool const result = nek::equal(a, a + 3, b);
    EXPECT_FALSE(result);
}

TEST(equal_test, container_true)
{
    std::list<int> const a = {1, 2, 3};
    std::list<int> const b = {1, 2, 3};
    bool const result = nek::equal(a.begin(), a.end(), b.begin());
    EXPECT_TRUE(result);
}

TEST(equal_test, container_false)
{
    std::list<int> const a = {1, 2, 3};
    std::list<int> const b = {1, 2, 4};
    bool const result = nek::equal(a.begin(), a.end(), b.begin());
    EXPECT_FALSE(result);
}
