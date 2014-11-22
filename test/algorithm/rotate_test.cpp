#include <nek/algorithm/rotate.hpp>
#include <gtest/gtest.h>
#include <forward_list>
#include <list>
#include <vector>

TEST(rotate_test, bidirectional1)
{
    std::list<int> actual = {1, 2, 3, 4};
    std::list<int> const expected = {2, 3, 4, 1};
    auto const middle = ++actual.begin();

    nek::rotate(actual.begin(), middle, actual.end());

    EXPECT_EQ(expected, actual);
}

TEST(rotate_test, bidirectional2)
{
    std::list<int> actual = {1, 2, 3, 4};
    std::list<int> const expected = {4, 1, 2, 3};
    auto const middle = --actual.end();

    nek::rotate(actual.begin(), middle, actual.end());

    EXPECT_EQ(expected, actual);
}

TEST(rotate_test, forward_iterator1)
{
    std::forward_list<int> actual = {1, 2, 3, 4};
    std::forward_list<int> const expected = {2, 3, 4, 1};
    auto const middle = ++actual.begin();

    nek::rotate(actual.begin(), middle, actual.end());

    EXPECT_EQ(expected, actual);
}

TEST(rotate_test, forward_iterator2)
{
    std::forward_list<int> actual = {1, 2, 3, 4};
    std::forward_list<int> const expected = {4, 1, 2, 3};
    auto const middle = ++++++actual.begin();

    nek::rotate(actual.begin(), middle, actual.end());

    EXPECT_EQ(expected, actual);
}

TEST(rotate_test, random_access1)
{
    std::vector<int> actual = {1, 2, 3, 4};
    std::vector<int> const expected = {2, 3, 4, 1};
    auto const middle = ++actual.begin();

    nek::rotate(actual.begin(), middle, actual.end());

    EXPECT_EQ(expected, actual);
}

TEST(rotate_test, random_access2)
{
    std::vector<int> actual = {1, 2, 3, 4};
    std::vector<int> const expected = {4, 1, 2, 3};
    auto const middle = --actual.end();

    nek::rotate(actual.begin(), middle, actual.end());

    EXPECT_EQ(expected, actual);
}