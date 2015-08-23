#ifndef NEK_CONTAINER_FUNCTION_EMPLACE_HPP
#define NEK_CONTAINER_FUNCTION_EMPLACE_HPP

#include <nek/utility/forward.hpp>

namespace nek
{
    template <class Container, class Iterator, class... Args>
    auto emplace(Container& con, Iterator position, Args&&... args)
    {
        return con.emplace(position, nek::forward<Args>(args)...);
    }
}

#endif
