#ifndef NEK_ALGORITHM_MAX_HPP
#define NEK_ALGORITHM_MAX_HPP

namespace nek
{
    template <class T>
    inline T const& max(T const& left, T const& right)
    {
        return left < right ? right : left;
    }
}

#endif