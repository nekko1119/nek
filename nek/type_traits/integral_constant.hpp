#ifndef NEK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define NEK_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

#include <type_traits>

namespace nek
{
    template <class T, T Value>
    struct integral_constant
    {
        typedef T value_type;
        typedef integral_constant<T, Value> type;
        operator value_type() const
        {
            return value;
        }
        static const value_type value = Value;
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;
}

#endif