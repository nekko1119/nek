#ifndef NEK_TYPE_TRAITS_HAS_POINTER_HPP
#define NEK_TYPE_TRAITS_HAS_POINTER_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
  namespace has_pointer_detail
  {
    template <class T, class U = T::pointer>
    true_type has_pointer(int);

    template <class>
    false_type has_pointer(long);
  }

  template <class T>
  struct has_pointer
    : public decltype(has_pointer_detail::has_pointer<T>(0))
  {
  };
}

#endif