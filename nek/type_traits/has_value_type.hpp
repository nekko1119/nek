#ifndef NEK_TYPE_TRAITS_HAS_VALUE_TYPE_HPP
#define NEK_TYPE_TRAITS_HAS_VALUE_TYPE_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
    namespace has_value_type_detail
    {
        template <class T, class = typename T::value_type>
        nek::true_type has_value_type(T*);

        template <class>
        nek::false_type has_value_type(...);
    }

    template <class T>
    struct has_value_type
        : public decltype(has_value_type_detail::has_value_type<T>(nullptr))
    {
    };
}

#endif