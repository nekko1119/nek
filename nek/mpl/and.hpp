#ifndef NEK_MPL_AND_HPP
#define NEK_MPL_AND_HPP

#include <nek/mpl/bool.hpp>

namespace nek
{
    namespace mpl
    {
        namespace and_detail
        {
            template <bool...>
            struct and_c_impl
                : public false_
            {
            };

            template <>
            struct and_c_impl<true>
                : public true_
            {
            };

            template <bool... Cs>
            struct and_c_impl<true, Cs...>
                : public and_c_impl<Cs...>
            {
            };

            template <bool, class...>
            struct and_impl
                : public false_
            {
            };

            template <>
            struct and_impl<true>
                : public true_
            {
            };

            template <class T, class... Ts>
            struct and_impl<true, T, Ts...>
                : public and_impl<T::type::value, Ts...>
            {
            };
        }

        template <bool... Cs>
        struct and_c
            : public and_detail::and_c_impl<Cs...>
        {
        };

        template <class T, class... Ts>
        struct and_
            : public and_detail::and_impl<T::type::value, Ts...>
        {
        };
    }
}

#endif
