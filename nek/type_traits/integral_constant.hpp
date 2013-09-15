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
        using type = integral_constant<T, N>;
    };

    template <>
    struct integral_constant<bool, true>
        : public mpl::true_
    {
        using type = integral_constant;
    };

    template <>
    struct integral_constant<bool, false>
        : public mpl::false_
    {
        using type = integral_constant;
    };

    using true_type = integral_constant<bool, true>;
    using false_type = integral_constant<bool, false>;
}

#endif