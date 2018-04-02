#ifndef NEK_TYPE_TRAITS_REMOVE_ALL_EXTENDS_HPP
#define NEK_TYPE_TRAITS_REMOVE_ALL_EXTENDS_HPP

#include <type_traits>

namespace nek
{
    template <class T>
    struct remove_all_extends
    {
        using type = T;
    };

    template <class T, std::size_t N>
    struct remove_all_extends<T[N]>
    {
        using type = typename remove_all_extends<T>::type;
    };

    template <class T>
    struct remove_all_extends<T[]>
    {
        using type = typename remove_all_extends<T>::type;
    };

    template <class T>
    using remove_all_extends_t = typename remove_all_extends<T>::type;
}

#endif
