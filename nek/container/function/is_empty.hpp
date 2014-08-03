#ifndef NEK_CONTAINER_FUNCTION_IS_EMPTY_HPP
#define NEK_CONTAINER_FUNCTION_IS_EMPTY_HPP

#include <cstddef>

namespace nek
{
  template <class Container>
  inline bool is_empty(Container const& con) noexcept
  {
    return con.begin() == con.end();
  }

  template <class T, std::size_t N>
  inline constexpr bool is_empty(T (&arr)[N]) noexcept
  {
    // return true if N == 0. but N is never 0.
    return false;
  }
}

#endif