#ifndef NEK_TYPE_TRAITS_HAS_VALUE_TYPE_HPP
#define NEK_TYPE_TRAITS_HAS_VALUE_TYPE_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
  namespace detail
  {
    template <class T, class U = T::value_type>
    true_type has_value_type(int);

    template <class>
    false_type has_value_type(long);
  }

  template <class T>
  struct has_value_type
    : public decltype(detail::has_value_type<T>(0))
  {
  };
}

#endif