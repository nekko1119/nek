#ifndef NEK_TYPE_TRAITS_IS_VOID_HPP
#define NEK_TYPE_TRAITS_IS_VOID_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
    namespace detail
    {
        template <class T>
        struct is_void
            : public false_type
        {
        };

        template <>
        struct is_void<void>
            : public true_type
        {
        };
    }

    template <class T>
    struct is_void
        : public detail::is_void<typename remove_cv<T>::type>
    {
    };
}

#endif