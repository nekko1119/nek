#ifndef NEK_CONTAINER_FUNCTION_PUSH_BACK_HPP
#define NEK_CONTAINER_FUNCTION_PUSH_BACK_HPP

#include <nek/container/function/emplace.hpp>
#include <nek/utility/forward.hpp>

namespace nek
{
    template <class Container, class T>
    void push_back(Container& con, T const& value)
    {
        nek::emplace(con, con.end(), value);
    }

    template <class Container, class T>
    void push_back(Container& con, T&& value)
    {
        nek::emplace(con, con.end(), nek::forward<T>(value));
    }
}

#endif
