#ifndef NEK_CONTAINER_FUNCTION_BACK_HPP
#define NEK_CONTAINER_FUNCTION_BACK_HPP

#include <cstddef>

namespace nek
{
  template <class Container>
  decltype(auto) back(Container& con)
  {
    return *--con.end();
  }

  template <class Container>
  decltype(auto) back(Container const& con)
  {
    return *--con.end();
  }

  template <class T, std::size_t N>
  constexpr decltype(auto) back(T(&array)[N])
  {
    return array[N - 1];
  }

  template <class T, std::size_t N>
  constexpr decltype(auto) back(T const (&array)[N])
  {
    return array[N - 1];
  }
}

#endif