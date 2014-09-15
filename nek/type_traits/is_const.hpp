#ifndef NEK_TYPE_TRAITS_IS_CONST_HPP
#define NEK_TYPE_TRAITS_IS_CONST_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_extends.hpp>

namespace nek
{
  namespace is_const_detail
  {
    template <class T>
    struct is_const_
      : public false_type
    {
    };

    template <class T>
    struct is_const_<T const>
      : public true_type
    {
    };
  }

  template <class T>
  struct is_const
    : public is_const_detail::is_const_<nek::remove_extends_t<T>>
  {
  };
}

#endif