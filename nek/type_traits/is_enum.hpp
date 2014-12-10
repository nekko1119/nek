#ifndef NEK_TYPE_TRAITS_IS_ENUM_HPP
#define NEK_TYPE_TRAITS_IS_ENUM_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
    template <class T>
    struct is_enum
        : public integral_constant<bool, __is_enum(remove_cv_t<T>)>
    {
    };
}
#endif