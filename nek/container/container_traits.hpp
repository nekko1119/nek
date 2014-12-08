#ifndef NEK_CONTAINER_CONTAINER_TRAITS_HPP
#define NEK_CONTAINER_CONTAINER_TRAITS_HPP

#include <cstddef>

namespace nek
{
    template <class Container>
    struct container_traits
    {
        using value_type = typename Container::value_type;
        using size_type = typename Container::size_type;
    };

    template <class T, std::size_t N>
    struct container_traits<T [N]>
    {
        using value_type = T;
        using size_type = std::size_t;
    };
}

#endif
