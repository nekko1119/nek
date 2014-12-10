#ifndef NEK_TYPE_TRAITS_IS_POINTER_HPP
#define NEK_TYPE_TRAITS_IS_POINTER_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
    namespace is_pointer_detail
    {
        template <class T>
        struct is_pointer
            : public false_type
        {
        };

        template <class T>
        struct is_pointer<T*>
            : public true_type
        {
        };
    }

    template <class T>
    struct is_pointer
        : public is_pointer_detail::is_pointer<remove_cv_t<T>>
    {
    };
}

#endif