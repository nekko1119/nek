#ifndef NEK_MPL_BOOL_HPP
#define NEK_MPL_BOOL_HPP

#include <nek/mpl/bool_fwd.hpp>
#include <nek/mpl/integral_c_tag.hpp>

namespace nek
{
    namespace mpl
    {
        template <bool C>
        struct bool_
        {
            static const bool value = C;
            typedef integral_c_tag tag;
            typedef bool_ type;
            typedef bool value_type;
            operator bool() const
            {
                return value;
            }
        };
    }
}

#endif