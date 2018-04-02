#include <nek/type_traits/enable_if.hpp>
#include <gtest/gtest.h>
#include <nek/type_traits/is_integral.hpp>

template <class T>
auto func_c(T const&) -> typename nek::enable_if_c<nek::is_integral<T>::value, bool>::type
{
    return true;
}

template <class T>
auto func_c(T const&) -> typename nek::disable_if_c<nek::is_integral<T>::value, bool>::type
{
    return false;
}

template <class T>
auto func(T const&) -> typename nek::enable_if<nek::is_integral<T>, bool>::type
{
    return true;
}

template <class T>
auto func(T const&) -> typename nek::disable_if<nek::is_integral<T>, bool>::type
{
    return false;
}

TEST(enable_if_c_test, normal)
{
    EXPECT_TRUE(func_c(0));
    EXPECT_FALSE(func_c(0.0));
    EXPECT_TRUE(func(0));
    EXPECT_FALSE(func(0.0));
}
