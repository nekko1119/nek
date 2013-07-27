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
            static const T value = N;
            typedef integral_c_tag tag;
            typedef integral_c type;
            typedef T value_type;
            typedef integral_c<T, N + 1> next;
            typedef integral_c<T, N - 1> prior;
            operator value_type() const
            {
                return value;
            }
        };

        //'bool' constant does not have 'next' and 'prior' members.
        template <bool C>
        struct integral_c<bool, C>
        {
            static const bool value = C;
            typedef integral_c_tag tag;
            typedef integral_c type;
            typedef bool value_type;
            operator bool() const
            {
                return value;
            }
        };
    }
}

#endif