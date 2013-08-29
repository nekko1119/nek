#ifndef NEK_TYPE_TRAITS_MAKE_UNSIGNED_HPP
#define NEK_TYPE_TRAITS_MAKE_UNSIGNED_HPP

#include <cstddef>
#include <nek/mpl/if.hpp>
#include <nek/type_traits/add_const.hpp>
#include <nek/type_traits/add_volatile.hpp>
#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/is_const.hpp>
#include <nek/type_traits/is_volatile.hpp>
#include <nek/type_traits/is_integral.hpp>
#include <nek/type_traits/is_enum.hpp>
#include <nek/type_traits/is_same.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
    namespace detail
    {
        template <class T>
        struct make_unsigned_from_integral
        {
            typedef T type;
        };

        template <>
        struct make_unsigned_from_integral<char>
        {
            typedef unsigned char type;
        };

        template <>
        struct make_unsigned_from_integral<signed char>
        {
            typedef unsigned char type;
        };

        template <>
        struct make_unsigned_from_integral<short>
        {
            typedef unsigned short type;
        };

        template <>
        struct make_unsigned_from_integral<int>
        {
            typedef unsigned int type;
        };

        template <>
        struct make_unsigned_from_integral<long>
        {
            typedef unsigned long type;
        };

        template <>
        struct make_unsigned_from_integral<long long>
        {
            typedef unsigned long long type;
        };

        template <class E>
        struct make_unsigned_from_enum
        {
        private:
            typedef unsigned char uc;
            typedef unsigned short us;
            typedef unsigned int ui;
            typedef unsigned long long ull;
            typedef typename mpl::if_c<sizeof(E) <= sizeof(ui), ui, ull>::type ui_or_big;
            typedef typename mpl::if_c<sizeof(E) <= sizeof(us), us, ui_or_big>::type us_or_big;
            typedef typename mpl::if_c<sizeof(E) <= sizeof(uc), uc, us_or_big>::type uc_or_big;

        public:
            typedef uc_or_big type;
        };

        template <class T, bool = is_integral<T>::value, bool = is_enum<T>::value>
        struct make_unsigned_impl;

        template <class T>
        struct make_unsigned_impl<T, true, false>
        {
            typedef typename make_unsigned_from_integral<T>::type type;
        };

        template <class T>
        struct make_unsigned_impl<T, false, true>
        {
            typedef typename make_unsigned_from_enum<T>::type type;
        };

        template <class Source, class Destination>
        struct match_cv_qualifiers
        {
        private:
            typedef typename mpl::if_<is_const<Source>, typename add_const<Destination>::type, Destination>::type c_type;
            typedef typename mpl::if_<is_volatile<Source>, typename add_volatile<c_type>::type, c_type>::type cv_type;
        
        public:
            typedef cv_type type;
        };
    }

    template <class T>
    struct make_unsigned
    {
        static_assert((is_integral<T>::value || is_enum<T>::value) && !(is_same<T, bool>::value || is_same<T, wchar_t>::value),
                      "T must be integral type(except bool and wchar_t) or enumeration type.");

    private:
        typedef typename detail::make_unsigned_impl<typename remove_cv<T>::type>::type noncv_unsigned_type;
    
    public:
        typedef typename detail::match_cv_qualifiers<T, noncv_unsigned_type>::type type;
    };
}

#endif