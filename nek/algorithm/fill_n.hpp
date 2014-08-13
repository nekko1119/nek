#ifndef NEK_ALGORITHM_FILL_N_HPP
#define NEK_ALGORITHM_FILL_N_HPP

#include <cstring>

namespace nek
{
  namespace fill_n_detail
  {
    char* fill_n_(char* dest, std::size_t count, char value)
    {
      std::memset(dest, value, count);
      return dest + count;
    }

    template <class OutputIterator, class Size, class T>
    OutputIterator fill_n_(OutputIterator dest, Size count, T const& value)
    {
      for (; 0 < count; --count, ++dest) {
        *dest = value;
      }
      return dest;
    }
  }
  template <class OutputIterator, class Size, class T>
  OutputIterator fill_n(OutputIterator dest, Size count, T const& value)
  {
    return fill_n_detail::fill_n_(dest, count, value);
  }
}

#endif