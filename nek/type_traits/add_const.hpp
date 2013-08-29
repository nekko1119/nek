#ifndef NEK_TYPE_TRAITS_ADD_CONST_HPP
#define NEK_TYPE_TRAITS_ADD_CONST_HPP

namespace nek
{
    template <class T>
    struct add_const
    {
        typedef const T type;
    };
}

#endif