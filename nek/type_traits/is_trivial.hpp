#ifndef NEK_TYPE_TRAITS_IS_TRIVIAL_HPP
#define NEK_TYPE_TRAITS_IS_TRIVIAL_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
    template <class T>
    struct is_trivial
        : public nek::integral_constant<bool, __is_trivial(nek::remove_cv_t<T>)>
    {
    };
}

#endif
