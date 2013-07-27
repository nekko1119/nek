#ifndef NEK_MPL_BOOL_FWD_HPP
#define NEK_MPL_BOOL_FWD_HPP

namespace nek
{
    namespace mpl
    {
        template <bool C>
        struct bool_;

        typedef bool_<true> true_;
        typedef bool_<false> false_;
    }
}

#endif