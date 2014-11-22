#ifndef NEK_TYPE_TRAITS_HAS_TYPE_HPP
#define NEK_TYPE_TRAITS_HAS_TYPE_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
    namespace has_type_detail
    {
        template <class T, class = typename T::type>
        true_type has_type(int);

        template <class>
        false_type has_type(long);
    }

    template <class T>
    struct has_type
        : public decltype(has_type_detail::has_type<T>(0))
    {
    };
}

#endif