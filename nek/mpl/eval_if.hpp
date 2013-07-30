#ifndef NEK_MPL_EVAL_IF_HPP
#define NEK_MPL_EVAL_IF_HPP

#include <nek/mpl/if.hpp>

namespace nek
{
    namespace mpl
    {
        template <bool C, class True, class False>
        struct eval_if_c
            : if_c<C, True, False>::type
        {
        };

        template <class Cond, class True, class False>
        struct eval_if
            : public if_<Cond, True, False>::type
        {
        };
    }
}

#endif