#ifndef NEK_UTILITY_SWAP_HPP
#define NEK_UTILITY_SWAP_HPP

#include <nek/utility/move.hpp>
#include <cstddef>

namespace nek
{
  namespace swap_detail
  {
    template <class T>
    inline void swap(T& left, T& right) noexcept
    {
      T swap_temp = move(left);
      left = move(right);
      right = move(swap_temp);
    }

    template <class T, std::size_t N>
    inline void swap(T (&left)[N], T (&right)[N]) noexcept
    {
      if (&left == &right) {
        return;
      }
      T* left_first = left;
      T* right_first = right;
      T* last = left + N;
      for (; left_first != last; ++left_first, ++right_first) {
        swap(*left_first, *right_first);
      } 
    }
  }

  template <class T>
  inline void swap(T& left, T& right) noexcept
  {
    using nek::swap_detail::swap;
    swap(left, right);
  }
}

#endif