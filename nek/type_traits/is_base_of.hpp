#ifndef NEK_TYPE_TRAITS_IS_BASE_OF_HPP
#define NEK_TYPE_TRAITS_IS_BASE_OF_HPP

#include <nek/mpl/and.hpp>
#include <nek/mpl/not.hpp>
#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/is_class.hpp>
#include <nek/type_traits/is_same.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
  namespace is_base_of_detail
  {
    template <class Base, class Derived, bool = mpl::and_c<nek::is_class<Base>::value, nek::is_class<Derived>::value, mpl::not_c<nek::is_same<Base, Derived>::value>::value>::value>
    struct is_base_of_
    {
    private:
      static nek::true_type check(Derived&, int);
      static nek::false_type check(Base&, long);

      struct host
      {
        operator Base&();
        operator Derived&();
      };

    public:
      using type = decltype(check(host{}, 0));
    };

    template <class Base, class Derived>
    struct is_base_of_<Base, Derived, false>
    {
      using type = nek::false_type;
    };

    template <class Base, class Derived>
    struct is_base_of_is_class
    {
      static constexpr bool value =
        is_base_of_<Base, Derived>::type::value ||
        nek::is_class<Base>::value && nek::is_same<Base, Derived>::value;
    };
  }

  template <class Base, class Derived>
  struct is_base_of
    : public nek::integral_constant<bool, is_base_of_detail::is_base_of_is_class<Base, Derived>::value>
  {
  };
}

#endif
