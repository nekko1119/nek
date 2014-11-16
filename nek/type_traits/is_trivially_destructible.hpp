#ifndef NEK_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
#define NEK_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP

#include <cstddef>
#include <nek/type_traits/integral_constant.hpp>
#ifndef _MSC_VER
#include <nek/mpl/and.hpp>
#include <type_traits> // TODO std::is_destructible
#endif

namespace nek
{
#ifdef _MSC_VER
    template <class T>
    struct is_trivially_destructible
        : public nek::integral_constant<bool, __has_trivial_destructor(T)>
    {
    };

    template <class T, std::size_t N>
    struct is_trivially_destructible<T[N]>
        : public nek::integral_constant<bool, __has_trivial_destructor(T)>
    {
    };
#else
    template <class T>
    struct is_trivially_destructible
        : public nek::integral_constant<bool, mpl::and_<std::is_destructible<T>, nek::integral_constant<bool, __has_trivial_destructor(T)>>::value>
    {
    };
#endif
}

#endif