#ifndef NEK_TYPE_TRAITS_HAS_TYPE_HPP
#define NEK_TYPE_TRAITS_HAS_TYPE_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
    namespace has_type_detail
    {
        template <class T, class = typename T::type>
        nek::true_type has_type(T*);

        template <class>
        nek::false_type has_type(...);
    }

    template <class T>
    struct has_type
        : public decltype(has_type_detail::has_type<T>(nullptr))
    {
    };
}

#endif