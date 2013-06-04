#ifndef NEK_UTILITY_FORWARD_HPP
#define NEK_UTILITY_FORWARD_HPP

#include <nek/type_traits/remove_reference.hpp>

namespace nek
{
    template <class T>
    inline T&& forward(typename remove_reference<T>::type& value)
    {
        return static_cast<T&&>(value);
    }

    template <class T>
    inline T&& forward(typename remove_reference<T>::type&& value)
    {
        return static_cast<T&&>(value);
    }
}

#endif