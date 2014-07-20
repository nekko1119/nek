#ifndef NEK_CONTAINER_FUNCTION_SIZE_HPP
#define NEK_CONTAINER_FUNCTION_SIZE_HPP

#include <cstddef>

namespace nek
{
  template <class Container>
  inline auto size(Container const& con) noexcept
  {
    return con.size();
  }

  template <class T, std::size_t N>
  inline constexpr std::size_t size(T(&arr)[N]) noexcept
  {
    return N;
  }
}

#endif