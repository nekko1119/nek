#ifndef NEK_CONTAINER_FUNCTION_EMPLACE_BACK_HPP
#define NEK_CONTAINER_FUNCTION_EMPLACE_BACK_HPP

#include <nek/utility/forward.hpp>

namespace nek
{
    template <class Container, class... Args>
    auto emplace_back(Container& con, Args&&... args)
    {
        return con.emplace(con.end(), nek::forward<Args>(args)...);
    }
}

#endif