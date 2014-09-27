#ifndef NEK_TYPE_TRAITS_IS_STATIC_CASTABLE_HPP
#define NEK_TYPE_TRAITS_IS_STATIC_cASTABLE_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/utility/declval.hpp>

namespace nek
{
  namespace is_static_castable_detail
  {
    template <class From, class To>
    struct is_static_castable_
    {
    private:
      template <class From2, class To2, class = decltype(static_cast<To>(nek::declval<From>()))>
      static nek::true_type check(int);

      template <class, class>
      static nek::false_type check(long);

    public:
      using type = decltype(check<From, To>(0));
    };
  }

  template <class From, class To>
  struct is_static_castable
    : is_static_castable_detail::is_static_castable_<From, To>::type
  {
  };
}

#endif
