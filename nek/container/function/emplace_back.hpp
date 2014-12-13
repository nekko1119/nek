#ifndef NEK_CONTAINER_FUNCTION_EMPLACE_BACK_HPP
#define NEK_CONTAINER_FUNCTION_EMPLACE_BACK_HPP

#include <nek/container/function/emplace.hpp>
#include <nek/utility/forward.hpp>

namespace nek
{
    template <class Container, class... Args>
    auto emplace_back(Container& con, Args&&... args)
    {
        return nek::emplace(con, con.end(), nek::forward<Args>(args)...);
    }
}

#endif