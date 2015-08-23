#ifndef NEK_MPL_INTEGRAL_C_HPP
#define NEK_MPL_INTEGRAL_C_HPP

#include <nek/mpl/integral_c_fwd.hpp>
#include <nek/mpl/integral_c_tag.hpp>

namespace nek
{
    namespace mpl
    {
        template <class T, T N>
        struct integral_c
        {
            static constexpr T value = N;
            using tag = integral_c_tag;
            using type = integral_c;
            using value_type = T;;
            using next = integral_c<T, N + 1>;;
            using prior = integral_c<T, N - 1>;
            operator value_type() const
            {
                return value;
            }
        };

        //　'bool' constant does not have 'next' and 'prior' members.
        template <bool C>
        struct integral_c<bool, C>
        {
            static constexpr bool value = C;
            using tag = integral_c_tag;
            using type = integral_c;
            using value_type = bool;
            operator bool() const
            {
                return value;
            }
        };
    }
}

#endif
