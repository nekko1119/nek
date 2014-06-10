#ifndef NEK_TYPE_TRAITS_MAKE_UNSIGNED_HPP
#define NEK_TYPE_TRAITS_MAKE_UNSIGNED_HPP

#include <cstddef>
#include <nek/mpl/if.hpp>
#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/is_integral.hpp>
#include <nek/type_traits/is_enum.hpp>
#include <nek/type_traits/is_same.hpp>
#include <nek/type_traits/remove_cv.hpp>
#include <nek/type_traits/propagate_cv.hpp>

namespace nek
{
  namespace detail
  {
    template <class T>
    struct make_unsigned_from_integral
    {
      using type = T;
    };

    template <>
    struct make_unsigned_from_integral<char>
    {
      using type = unsigned char;
    };

    template <>
    struct make_unsigned_from_integral<signed char>
    {
      using type = unsigned char;
    };

    template <>
    struct make_unsigned_from_integral<short>
    {
      using type = unsigned short;
    };

    template <>
    struct make_unsigned_from_integral<int>
    {
      using type = unsigned int;
    };

    template <>
    struct make_unsigned_from_integral<long>
    {
      using type = unsigned long;
    };

    template <>
    struct make_unsigned_from_integral<long long>
    {
      using type = unsigned long long;
    };

    template <class E>
    struct make_unsigned_from_enum
    {
    private:
      using uc = unsigned char;
      using us = unsigned short;
      using ui = unsigned int;
      using ul = unsigned long;
      using ull = unsigned long long;
      using ul_or_big = mpl::if_c_t<sizeof(E) <= sizeof(ul), ul, ull>;
      using ui_or_big = mpl::if_c_t<sizeof(E) <= sizeof(ui), ui, ul_or_big>;
      using us_or_big = mpl::if_c_t<sizeof(E) <= sizeof(us), us, ui_or_big>;
      using uc_or_big = mpl::if_c_t<sizeof(E) <= sizeof(uc), uc, us_or_big>;

    public:
      using type = uc_or_big;
    };

    template <class T, bool = is_integral<T>::value, bool = is_enum<T>::value>
    struct make_unsigned_impl;

    template <class T>
    struct make_unsigned_impl<T, true, false>
    {
      using type = typename make_unsigned_from_integral<T>::type;
    };

    template <class T>
    struct make_unsigned_impl<T, false, true>
    {
      using type = typename make_unsigned_from_enum<T>::type;
    };
  }

  template <class T>
  struct make_unsigned
  {
    static_assert((is_integral<T>::value || is_enum<T>::value) && !(is_same<T, bool>::value || is_same<T, wchar_t>::value),
    "T must be integral type(except bool and wchar_t) or enumeration type.");

  private:
    using noncv_unsigned_type = typename detail::make_unsigned_impl<remove_cv_t<T>>::type;

  public:
    using type = propagate_cv_t<T, noncv_unsigned_type>;
  };

  template <class T>
  using make_unsigned_t = typename make_unsigned<T>::type;
}

#endif