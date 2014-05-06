#ifndef NEK_TYPE_TRAITS_IS_POINTER_HPP
#define NEK_TYPE_TRAITS_IS_POINTER_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
  namespace detail
  {
    template <class T>
    struct is_pointer
      : public false_type
    {
    };

    template <class T>
    struct is_pointer<T*>
      : public true_type
    {
    };
  }

  template <class T>
  struct is_pointer
    : public detail::is_pointer<remove_cv_t<T>>
  {
  };
}

#endif