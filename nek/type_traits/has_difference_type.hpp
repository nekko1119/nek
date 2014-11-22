#ifndef NEK_TYPE_TRAITS_HAS_DIFFERENCE_TYPE_HPP
#define NEK_TYPE_TRAITS_HAS_DIFFERENCE_TYPE_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
    namespace difference_type_detail
    {
        template <class T, class U = typename T::difference_type>
        true_type has_difference_type(int);

        template <class>
        false_type has_difference_type(long);
    }

    template <class T>
    struct has_difference_type
        : public decltype(difference_type_detail::has_difference_type<T>(0))
    {
    };
}

#endif