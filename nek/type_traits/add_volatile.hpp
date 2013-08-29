#ifndef NEK_TYPE_TRAITS_ADD_VOLATILE_HPP
#define NEK_TYPE_TRAITS_ADD_VOLATILE_HPP

namespace nek
{
    template <class T>
    struct add_volatile
    {
        typedef volatile T type;
    };
}

#endif