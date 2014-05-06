#ifndef NEK_TYPE_TRAITS_IS_CONST_HPP
#define NEK_TYPE_TRAITS_IS_CONST_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
  template <class T>
  struct is_const
    : public false_type
  {
  };

  template <class T>
  struct is_const<T const>
    : public true_type
  {
  };
}

#endif