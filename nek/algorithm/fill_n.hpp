#ifndef NEK_ALGORITHM_FILL_N_HPP
#define NEK_ALGORITHM_FILL_N_HPP

#include <cstring>

namespace nek
{
  namespace fill_n_detail
  {
    template <class OutputIterator, class Size, class T>
    inline OutputIterator fill_n_(OutputIterator dest, Size count, T const& value)
    {
      for (; 0 < count; --count, ++dest) {
        *dest = value;
      }
      return dest;
    }

    template <>
    inline char* fill_n_<char*, std::size_t, char>(char* dest, std::size_t count, char const& value)
    {
      std::memset(dest, value, count);
      return dest + count;
    }

    inline signed char* fill_n_(signed char* dest, std::size_t count, signed char value)
    {
      std::memset(dest, value, count);
      return dest + count;
    }

    inline unsigned char* fill_n_(unsigned char* dest, std::size_t count, unsigned char value)
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