#ifndef NEK_TYPE_TRAITS_REMOVE_CONST_HPP
#define NEK_TYPE_TRAITS_REMOVE_CONST_HPP

namespace nek
{
    template <class T>
    struct remove_const
    {
        typedef T type;
    };

    template <class T>
    struct remove_const<const T>
    {
        typedef T type;
    };
}

#endif