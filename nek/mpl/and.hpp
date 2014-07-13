#ifndef NEK_MPL_AND_HPP
#define NEK_MPL_AND_HPP

#include <nek/mpl/bool.hpp>

namespace nek
{
  namespace mpl
  {
    namespace and_detail
    {
      template <bool C, bool...>
      struct and_c_impl
        : public false_
      {
      };

      template <>
      struct and_c_impl<true>
        : public true_
      {
      };

      template <bool C, bool... Cs>
      struct and_c_impl<true, C, Cs...>
        : public and_c_impl<C, Cs...>
      {
      };

      template <bool C, class... Ts>
      struct and_impl
        : public false_
      {
      };

      template <>
      struct and_impl<true>
        : public true_
      {
      };

      template <class T, class... Ts>
      struct and_impl<true, T, Ts...>
        : public and_impl<T::type::value, Ts...>
      {
      };
    }

    template <bool C, bool... Cs>
    struct and_c
      : public and_detail::and_c_impl<C, Cs...>
    {
    };

    template <class T, class... Ts>
    struct and_
      : public and_detail::and_impl<T::type::value, Ts...>
    {
    };
  }
}

#endif