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
            using type = True;
        };

        template <class True, class False>
        struct if_c<false, True, False>
        {
            using type = False;
        };

        template <bool Cond, class True, class False>
        using if_c_t = typename if_c<Cond, True, False>::type;

        template <class Cond, class True, class False>
        struct  if_
            : public if_c<Cond::value, True, False>
        {
        };

        template <class Cond, class True, class False>
        using if_t = typename if_<Cond, True, False>::type;
    }
}

#endif