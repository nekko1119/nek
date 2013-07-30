#ifndef NEK_TYPE_TRAITS_HAS_TYPE_HPP
#define NEK_TYPE_TRAITS_HAS_TYPE_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
    namespace detail
    {
        template <class T, class U = T::type>
        true_type has_type(int);

        template <class>
        false_type has_type(long);
    }

    template <class T>
    struct has_type
        : public decltype(detail::has_type<T>(0))
    {
    };
}

#endif