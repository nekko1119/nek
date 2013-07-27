#ifndef NEK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define NEK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

#include <nek/mpl/integral_c.hpp>
#include <nek/mpl/bool.hpp>

namespace nek
{
    template <class T, T N>
    struct integral_constant
        : public mpl::integral_c<T, N>
    {
        typedef integral_constant<T, N> type;
    };

    template <>
    struct integral_constant<bool, true>
        : public mpl::true_
    {
        typedef integral_constant type;
    };

    template <>
    struct integral_constant<bool, false>
        : public mpl::false_
    {
        typedef integral_constant type;
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;
}

#endif