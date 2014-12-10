#ifndef NEK_TYPE_TRAITS_IS_CLASS_HPP
#define NEK_TYPE_TRAITS_IS_CLASS_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
    template <class T>
    struct is_class
        : public integral_constant<bool, __is_class(remove_cv_t<T>)>
    {
    };
}

#endif