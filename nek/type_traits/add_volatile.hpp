#ifndef NEK_TYPE_TRAITS_ADD_VOLATILE_HPP
#define NEK_TYPE_TRAITS_ADD_VOLATILE_HPP

namespace nek
{
    template <class T>
    struct add_volatile
    {
        using type = T volatile;
    };

    template <class T>
    using add_volatile_t = typename add_volatile<T>::type;
}

#endif