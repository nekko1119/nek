#ifndef NEK_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP
#define NEK_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP

#include <nek/mpl/and.hpp>
#include <nek/mpl/not.hpp>
#include <nek/type_traits/is_reference.hpp>
#include <nek/type_traits/is_void.hpp>
#include <nek/type_traits/remove_reference.hpp>

namespace nek
{
    namespace add_lvalue_reference_detail
    {
        using mpl::and_;
        using nek::mpl::not_;
        template <class T,
            bool = and_<not_<is_reference<T>>, not_<is_void<T>>>::value,
            bool = is_rvalue_reference<T>::value>
        struct add_lvalue_reference
        {
            using type = T;
        };

        template <class T>
        struct add_lvalue_reference<T, true, false>
        {
            using type = T&;
        };

        template <class T>
        struct add_lvalue_reference<T, false, true>
        {
            using type = remove_reference_t<T>&;
        };
    }

    template <class T>
    struct add_lvalue_reference
        : public add_lvalue_reference_detail::add_lvalue_reference<T>
    {
    };

    template <class T>
    using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
}

#endif