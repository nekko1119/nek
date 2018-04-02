#ifndef NEK_TYPE_TRAITS_HAS_POINTER_HPP
#define NEK_TYPE_TRAITS_HAS_POINTER_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/void_t.hpp>

namespace nek
{
    template <class, class = void>
    struct has_pointer
        : public false_type
    {
    };

    template <class T>
    struct has_pointer<T, void_t<typename T::pointer>>
        : public true_type
    {
    };
}

#endif
