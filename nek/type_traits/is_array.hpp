#ifndef NEK_TYPE_TRAITS_IS_ARRAY_HPP
#define NEK_TYPE_TRAITS_IS_ARRAY_HPP

#include <cstddef>
#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
    template <class T>
    struct is_array
        : false_type
    {
    };

    template <class T>
    struct is_array<T[]>
        : true_type
    {
    };

    template <class T, std::size_t N>
    struct is_array<T[N]>
        : true_type
    {
    };
}

#endif
