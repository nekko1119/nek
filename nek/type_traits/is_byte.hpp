#ifndef NEK_TYPE_TRAITS_IS_BYTE_HPP
#define NEK_TYPE_TRAITS_IS_BYTE_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
    template <class T>
    struct is_byte
        : public false_type
    {
    };

    template <>
    struct is_byte<char>
        : public true_type
    {
    };

    template <>
    struct is_byte<signed char>
        : public true_type
    {
    };

    template <>
    struct is_byte<unsigned char>
        : public true_type
    {
    };
}

#endif