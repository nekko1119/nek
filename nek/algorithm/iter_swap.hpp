#ifndef NEK_ALGORITHM_ITER_SWAP_HPP
#define NEK_ALGORITHM_ITER_SWAP_HPP

#include <nek/utility/swap.hpp>

namespace nek
{
    template <class LeftForwardIterator, class RightForwardIterator>
    inline void iter_swap(LeftForwardIterator left, RightForwardIterator right) noexcept
    {
        using nek::swap;
        swap(*left, *right);
    }
}

#endif