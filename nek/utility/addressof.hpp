#ifndef NEK_UTILITY_ADDRESSOF_HPP
#define NEK_UTILITY_ADDRESSOF_HPP

namespace nek
{
    template <class T>
    inline T* addressof(T& value)
    {
        return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(value)));
    }
}

#endif