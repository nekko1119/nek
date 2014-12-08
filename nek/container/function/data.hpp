#ifndef NEK_CONTAINER_FUNCTION_DATA_HPP
#define NEK_CONTAINER_FUNCTION_DATA_HPP

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
    inline constexpr T* data(T (&ar[N]))
    {
        return ar;
    }

    template <class T, std::size_t N>
    inline constexpr T const* data(T const (&ar[N]))
    {
        return ar;
    }
}

#endif