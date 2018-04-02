#ifndef NEK_TYPE_TRAITS_IS_REFERENCE_HPP
#define NEK_TYPE_TRAITS_IS_REFERENCE_HPP

#include <nek/type_traits/is_lvalue_reference.hpp>
#include <nek/type_traits/is_rvalue_reference.hpp>

namespace nek
{
    template <class T>
    struct is_reference
        : public integral_constant<bool, is_lvalue_reference<T>::value || is_rvalue_reference<T>::value>
    {
    };
}

#endif
