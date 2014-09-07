#ifndef NEK_ALGORITHM_MIN_HPP
#define NEK_ALGORITHM_MIN_HPP

namespace nek
{
  template <class T>
  inline T const& min(T const& left, T const& right)
  {
    return left < right ? left : right;
  }
}

#endif