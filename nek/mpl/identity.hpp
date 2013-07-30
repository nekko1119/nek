#ifndef NEK_MPL_IDENTITY_HPP
#define NEK_MPL_IDENTITY_HPP

namespace nek
{
    namespace mpl
    {
        template <class T>
        struct identity
        {
            typedef T type;
        };
    }
}

#endif