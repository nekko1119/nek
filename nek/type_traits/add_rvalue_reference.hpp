#ifndef NEK_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP
#define NEK_TYPE_TRAITS_ADD_RVALUE_REFERENCE_HPP

#include <nek/mpl/and.hpp>
#include <nek/mpl/not.hpp>
#include <nek/type_traits/is_reference.hpp>
#include <nek/type_traits/is_void.hpp>
#include <nek/type_traits/remove_reference.hpp>

namespace nek
{
  namespace add_rvalue_reference_detail
  {
    using mpl::and_;
    using nek::mpl::not_;
    template <class T,
      bool = and_<not_<is_reference<T>>, not_<is_void<T>>>::value>
    struct add_rvalue_reference
    {
      using type = T;
    };

    template <class T>
    struct add_rvalue_reference<T, true>
    {
      using type = T&&;
    };
  }

  template <class T>
  struct add_rvalue_reference
    : public add_rvalue_reference_detail::add_rvalue_reference<T>
  {
  };

  template <class T>
  using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
}
#endif