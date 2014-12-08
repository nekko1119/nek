#ifndef NEK_CONTAINER_VECTOR_OPERATOR_HPP
#define NEK_CONTAINER_VECTOR_OPERATOR_HPP

#include <nek/algorithm/equal.hpp>
#include <nek/algorithm/lexicographical_compare.hpp>
#include <nek/container/vector/vector.hpp>

namespace nek
{
    template <class T, class Allocator>
    inline bool operator==(vector<T, Allocator> const& left, vector<T, Allocator> const& right)
    {
        return nek::size(left) == nek::size(right) && nek::equal(left.begin(), left.end(), right.begin());
    }

    template <class T, class Allocator>
    inline bool operator!=(vector<T, Allocator> const& left, vector<T, Allocator> const& right)
    {
        return !(left == right);
    }

    template <class T, class Allocator>
    inline bool operator<(vector<T, Allocator> const& left, vector<T, Allocator> right) noexcept
    {
        return nek::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end());
    }

        template <class T, class Allocator>
    inline bool operator>(vector<T, Allocator> const& left, vector<T, Allocator> right) noexcept
    {
        return right < left;
    }

        template <class T, class Allocator>
    inline bool operator<=(vector<T, Allocator> const& left, vector<T, Allocator> right) noexcept
    {
        return !(right < left);
    }

        template <class T, class Allocator>
    inline bool operator>=(vector<T, Allocator> const& left, vector<T, Allocator> right) noexcept
    {
        return !(left < right);
    }
}

#endif
