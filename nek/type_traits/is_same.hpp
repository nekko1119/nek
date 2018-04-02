#ifndef NEK_TYPE_TRAITS_IS_SAME_HPP
#define NEK_TYPE_TRAITS_IS_SAME_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
    template <class T, class U>
    struct is_same
        : public false_type
    {
    };

    template <class T>
    struct is_same<T, T>
        : public true_type
    {
    };

}

#endif
