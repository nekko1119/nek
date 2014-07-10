#ifndef NEK_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP
#define NEK_TYPE_TRAITS_IS_TRIVIALLY_DESTRUCTIBLE_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
  template <class T>
  struct is_trivially_destructible
    : public nek::integral_constant<bool, __has_trivial_destructor(T)>
  {
  };
}

#endif