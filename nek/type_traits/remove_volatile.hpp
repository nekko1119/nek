#ifndef NEK_TYPE_TRAITS_REMOVE_VOLATILE_HPP
#define NEK_TYPE_TRAITS_REMOVE_VOLATILE_HPP

namespace nek
{
    template <class T>
    struct remove_volatile
    {
        using type = T;
    };

    template <class T>
    struct remove_volatile<volatile T>
    {
        using type = T;
    };

    template <class T>
    using remove_volatile_t = typename remove_volatile<T>::type;
}

#endif