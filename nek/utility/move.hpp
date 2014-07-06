#ifndef NEK_UTILITY_MOVE_HPP
#define NEK_UTILITY_MOVE_HPP

#include <nek/type_traits/remove_reference.hpp>

namespace nek
{
  template <class T>
  inline remove_reference_t<T>&& move(T&& value) noexcept
  {
    return static_cast<remove_reference_t<T>&&>(value);
  }
}

#endif