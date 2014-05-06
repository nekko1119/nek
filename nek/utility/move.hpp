#ifndef NEK_UTILITY_MOVE_HPP
#define NEK_UTILITY_MOVE_HPP

#include <nek/type_traits/remove_reference.hpp>

namespace nek
{
  template <class T>
  inline typename remove_reference<T>::type&& move(T&& value)
  {
    return static_cast<remove_reference_t<T>&&>(value);
  }
}

#endif