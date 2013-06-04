#ifndef NEK_MPL_IF_HPP
#define NEK_MPL_IF_HPP

namespace nek
{
    namespace mpl
    {
        template <bool Cond, class True, class False>
        struct if_c;

        template <class True, class False>
        struct if_c<true, True, False>
        {
            typedef True type;
        };

        template <class True, class False>
        struct if_c<false, True, False>
        {
            typedef False type;
        };

        template <class Cond, class True, class False>
        struct  if_
            : public if_c<Cond::value, True, False>
        {
        };
    }
}

#endif