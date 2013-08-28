#ifndef NEK_TYPE_TRAITS_IS_VOLATILE_HPP
#define NEK_TYPE_TRAITS_IS_VOLATILE_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
    template <class T>
    struct is_volatile
        : public false_type
    {
    };

    template <class T>
    struct is_volatile<volatile T>
        : public true_type
    {
    };
}

#endif