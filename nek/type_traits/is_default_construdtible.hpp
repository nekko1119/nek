#ifndef NEK_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP
#define NEK_TYPE_TRAITS_IS_DEFAULT_CONSTRUCTIBLE_HPP

#include <type_traits> // TODO : std::extent
#include <nek/mpl/and.hpp>
#include <nek/mpl/not.hpp>
#include <nek/type_traits/is_array.hpp>
#include <nek/type_traits/is_void.hpp>
#include <nek/type_traits/remove_all_extends.hpp>

namespace nek
{
  namespace is_default_constructible_detail
  {
    template <class T>
    struct is_default_constructible_
    {
    private:
      template <class U, class = decltype(U())>
      static nek::true_type check(int);

      template <class U>
      static nek::false_type check(long);

    public:
      using type = decltype(check<T>(0));
    };

    template <class T>
    struct is_default_constructible_not_void
      : public mpl::and_<mpl::not_<is_void<T>>, is_default_constructible_<T>>
    {
    };

    template <class T, bool = nek::is_array<T>::value>
    struct is_default_constructible_is_array;

    template <class T>
    struct is_default_constructible_is_array<T, true>
      : public mpl::and_c<
      (std::extent<T>::value > 0),
      is_default_constructible_not_void<remove_all_extends_t<T>>::value>
    {
    };
    
    template <class T>
    struct is_default_constructible_is_array<T, false>
      : public is_default_constructible_not_void<T>
    {
    };
  }

  template <class T>
  struct is_default_constructible
    : public nek::integral_constant<bool, is_default_constructible_detail::is_default_constructible_is_array<T>::value>
  {
  };
}

#endif
