#ifndef NEK_TYPE_TRAITS_HAS_POINTER_HPP
#define NEK_TYPE_TRAITS_HAS_POINTER_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
    namespace has_pointer_detail
    {
        template <class T, class = typename T::pointer>
        nek::true_type has_pointer(T*);

        template <class>
        nek::false_type has_pointer(...);
    }

    template <class T>
    struct has_pointer
        : public decltype(has_pointer_detail::has_pointer<T>(nullptr))
    {
    };
}

#endif