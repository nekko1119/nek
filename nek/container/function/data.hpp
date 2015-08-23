#ifndef NEK_CONTAINER_FUNCTION_DATA_HPP
#define NEK_CONTAINER_FUNCTION_DATA_HPP

#include <cstddef>

namespace nek
{
    template <class Container>
    inline auto data(Container& con)
    {
        return con.data();
    }

    template <class Container>
    inline auto data(Container const& con)
    {
        return con.data();
    }

    template <class T, std::size_t N>
    inline constexpr T* data(T (&array)[N])
    {
        return array;
    }

    template <class T, std::size_t N>
    inline constexpr T const* data(T const (&array)[N])
    {
        return array;
    }
}

#endif
