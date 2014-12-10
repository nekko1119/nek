#ifndef NEK_TYPE_TRAITS_IS_SIGNED_HPP
#define NEK_TYPE_TRAITS_IS_SIGNED_HPP

#include <nek/type_traits/is_floating_point.hpp>
#include <nek/type_traits/is_integral.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
    namespace is_sgined_detail
    {
        template <class T, bool = nek::is_integral<T>::value, bool = nek::is_floating_point<T>::value>
        struct is_signed_
            : public false_type
        {
        };

        template <class T>
        struct is_signed_<T, false, true>
            : public true_type
        {
        };

        template <class T>
        struct is_signed_<T, true, false>
            : public nek::integral_constant<bool, static_cast<bool>(T(-1) < T(0))>
        {
        };
    }

    template <class T>
    struct is_signed
        : public is_sgined_detail::is_signed_<nek::remove_cv_t<T>>
    {
    };
}

#endif
