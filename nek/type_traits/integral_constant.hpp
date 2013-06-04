#ifndef NEK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define NEK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

#include <type_traits>

namespace nek
{
    template <class T, T Val>
    struct integral_constant
    {
        typedef T value_type;
        operator value_type() const
        {
            return value;
        }
        static const value_type value = Val;
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;
}

#endif