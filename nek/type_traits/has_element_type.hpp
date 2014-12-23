#ifndef NEK_TYPE_TRAITS_HAS_ELEMENT_TYPE_HPP
#define NEK_TYPE_TRAITS_HAS_ELEMENT_TYPE_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
    namespace has_element_detail
    {
        template <class T, class = typename T::element_type>
        nek::true_type has_element_type(T*);

        template <class>
        nek::false_type has_element_type(...);
    }

    template <class T>
    struct has_element_type
        : public decltype(has_element_detail::has_element_type<T>(nullptr))
    {
    };
}

#endif