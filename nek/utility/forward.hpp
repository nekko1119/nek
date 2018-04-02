#ifndef NEK_UTILITY_FORWARD_HPP
#define NEK_UTILITY_FORWARD_HPP

#include <nek/type_traits/remove_reference.hpp>

namespace nek
{
    template <class T>
    inline T&& forward(remove_reference_t<T>& value) noexcept
    {
        return static_cast<T&&>(value);
    }

    template <class T>
    inline T&& forward(remove_reference_t<T>&& value) noexcept = delete;
}

#endif
