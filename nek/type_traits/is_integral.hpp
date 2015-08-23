#ifndef NEK_TYPE_TRAITS_IS_INTEGRAL_HPP
#define NEK_TYPE_TRAITS_IS_INTEGRAL_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
    namespace is_integral_detail
    {
        template <class T>
        struct is_integral
            : public false_type
        {
        };

        template <>
        struct is_integral<bool>
            : public true_type
        {
        };

        template <>
        struct is_integral<wchar_t>
            : public true_type
        {
        };

        template <>
        struct is_integral<char>
            : public true_type
        {
        };

        template <>
        struct is_integral<signed char>
            : public true_type
        {
        };

        template <>
        struct is_integral<unsigned char>
            : public true_type
        {
        };

        template <>
        struct is_integral<signed short>
            : public true_type
        {
        };

        template <>
        struct is_integral<unsigned short>
            : public true_type
        {
        };

        template <>
        struct is_integral<signed int>
            : public true_type
        {
        };

        template <>
        struct is_integral<unsigned int>
            : public true_type
        {
        };

        template <>
        struct is_integral<signed long>
            : public true_type
        {
        };

        template <>
        struct is_integral<unsigned long>
            : public true_type
        {
        };

        template <>
        struct is_integral<long long>
            : public true_type
        {
        };

        template <>
        struct is_integral<unsigned long long>
            : public true_type
        {
        };
    }

    template <class T>
    struct is_integral
        : public is_integral_detail::is_integral<remove_cv_t<T>>
    {
    };
}

#endif
