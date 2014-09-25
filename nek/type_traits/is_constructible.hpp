#ifndef NEK_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
#define NEK_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP

#include <nek/type_traits/is_default_construdtible.hpp>
#include <nek/utility/declval.hpp>

namespace nek
{
  namespace is_constructible_detail
  {
    template <class T, class... Args>
    struct is_constructible_impl
    {
    private:
      template <class T2, class... Args2, class = decltype(T2(nek::declval<Args2>()...))>
      static nek::true_type check(int);

      template <class, class...>
      static nek::false_type check(long);

    public:
      using type = decltype(check<T, Args...>(0));
    };

    template <class T, class... Args>
    struct is_constructible_
      : public is_constructible_impl<T, Args...>::type
    {
    };

    template <class T>
    struct is_constructible_<T>
      : nek::is_default_constructible<T>
    {
    };
  }

  template <class T, class... Args>
  struct is_constructible
    : public is_constructible_detail::is_constructible_<T, Args...>
  {
  };
}

#endif