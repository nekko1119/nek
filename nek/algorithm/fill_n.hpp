#ifndef NEK_ALGORITHM_FILL_N_HPP
#define NEK_ALGORITHM_FILL_N_HPP

#include <cstring>

#include <nek/type_traits/is_byte.hpp>

namespace nek
{
  namespace fill_n_detail
  {
    template <class OutputIterator, class Size, class T>
    inline OutputIterator fill_n_(OutputIterator dest, Size count, T const& value, nek::false_type)
    {
      for (; 0 < count; --count, ++dest) {
        *dest = value;
      }
      return dest;
    }

    template <class T, class Size>
    inline char* fill_n_(T* dest, Size count, T const& value, nek::true_type)
    {
      std::memset(dest, value, count);
      return dest + count;
    }
  }

  template <class OutputIterator, class Size, class T>
  inline OutputIterator fill_n(OutputIterator dest, Size count, T const& value)
  {
    return fill_n_detail::fill_n_(dest, count, value, is_byte<T>{});
  }
}

#endif