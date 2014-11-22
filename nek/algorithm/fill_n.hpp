#ifndef NEK_ALGORITHM_FILL_N_HPP
#define NEK_ALGORITHM_FILL_N_HPP

#include <cstring>

#include <nek/type_traits/is_byte.hpp>
#include <nek/type_traits/enable_if.hpp>

namespace nek
{
    namespace fill_n_detail
    {
        template <class OutputIterator, class Size, class T>
        inline nek::disable_if_t<is_byte<T>, OutputIterator> fill_n_(OutputIterator dest, Size count, T const& value)
        {
            for (; 0 < count; --count, ++dest) {
                *dest = value;
            }
            return dest;
        }

        template <class T, class Size>
        inline nek::enable_if_t<is_byte<T>, T*> fill_n_(T* dest, Size count, T const& value)
        {
            std::memset(dest, value, count);
            return dest + count;
        }
    }

    template <class OutputIterator, class Size, class T>
    inline OutputIterator fill_n(OutputIterator dest, Size count, T const& value)
    {
        return fill_n_detail::fill_n_(dest, count, value);
    }
}

#endif