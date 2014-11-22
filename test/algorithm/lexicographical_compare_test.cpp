#include <nek/algorithm/lexicographical_compare.hpp>
#include <gtest/gtest.h>
#include <string>

TEST(lexicographical_compare_test, char)
{
    {
        char const* left = "abc";
        char const* right = "abc";
        EXPECT_FALSE(
            nek::lexicographical_compare(
            left, left + 3, right, right + 3));
    }
    {
        char const* left = "abcd";
        char const* right = "abc";
        EXPECT_FALSE(
            nek::lexicographical_compare(
            left, left + 4, right, right + 3));
    }
    {
        char const* left = "abC";
        char const* right = "abc";
        EXPECT_TRUE(
            nek::lexicographical_compare(
            left, left + 3, right, right + 3));
    }
}

TEST(lexicographical_compare_test, char_pred)
{
    {
        char const* left = "abc";
        char const* right = "abc";
        EXPECT_FALSE(
            nek::lexicographical_compare(
            left, left + 3, right, right + 3, [](auto l, auto r){return l < r; }));
    }
    {
        char const* left = "abcd";
        char const* right = "abc";
        EXPECT_FALSE(
            nek::lexicographical_compare(
            left, left + 4, right, right + 3, [](auto l, auto r){return l < r; }));
    }
    {
        char const* left = "abC";
        char const* right = "abc";
        EXPECT_TRUE(
            nek::lexicographical_compare(
            left, left + 3, right, right + 3, [](auto l, auto r){return l < r; }));
    }
}

TEST(lexicographical_compare_test, string)
{
    {
        std::string const left = "abc";
        std::string const right = "abc";
        EXPECT_FALSE(
            nek::lexicographical_compare(
            left.begin(), left.end(), right.begin(), right.end()));
    }
    {
        std::string const left = "abcd";
        std::string const right = "abc";
        EXPECT_FALSE(
            nek::lexicographical_compare(
            left.begin(), left.end(), right.begin(), right.end()));
    }
    {
        std::string const left = "abC";
        std::string const right = "abc";
        EXPECT_TRUE(
            nek::lexicographical_compare(
            left.begin(), left.end(), right.begin(), right.end()));
    }
}

TEST(lexicographical_compare_test, string_pred)
{
    {
        std::string const left = "abc";
        std::string const right = "abc";
        EXPECT_FALSE(
            nek::lexicographical_compare(
            left.begin(), left.end(), right.begin(), right.end(), [](auto l, auto r){return l < r; }));
    }
    {
        std::string const left = "abcd";
        std::string const right = "abc";
        EXPECT_FALSE(
            nek::lexicographical_compare(
            left.begin(), left.end(), right.begin(), right.end(), [](auto l, auto r){return l < r; }));
    }
    {
        std::string const left = "abC";
        std::string const right = "abc";
        EXPECT_TRUE(
            nek::lexicographical_compare(
            left.begin(), left.end(), right.begin(), right.end(), [](auto l, auto r){return l < r; }));
    }
}