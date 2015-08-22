#ifndef NEK_TYPE_TRAITS_HAS_VALUE_TYPE_HPP
#define NEK_TYPE_TRAITS_HAS_VALUE_TYPE_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/void_t.hpp>

namespace nek
{
    template <class, class = void>
    struct has_value_type
        : public false_type
    {
    };

    template <class T>
    struct has_value_type<T, void_t<typename T::value_type>>
        : public true_type
    {
    };
}

#endif