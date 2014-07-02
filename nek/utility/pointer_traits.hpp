#ifndef NEK_UTILITY_POINTER_TRAITS_HPP
#define NEK_UTILITY_POINTER_TRAITS_HPP

#include <cstddef>
#include <nek/mpl/if.hpp>
#include <nek/type_traits/has_difference_type.hpp>
#include <nek/type_traits/has_element_type.hpp>
#include <nek/type_traits/is_void.hpp>
#include <nek/utility/addressof.hpp>

namespace nek
{
  namespace pointer_traits_detail
  {
    template <class T, bool = nek::has_element_type<T>::value>
    struct element_type
    {
      using type = typename T::element_type;
    };

    template <template <class, class...> class Ptr, class T, class... Args>
    struct element_type<Ptr<T, Args...>, false>
    {
      using type = T;
    };

    template <class T, bool = nek::has_difference_type<T>::value>
    struct difference_type
    {
      using type = typename T::difference_type;
    };

    template <class T>
    struct difference_type<T, false>
    {
      using type = std::ptrdiff_t;
    };

    template <class T, class U, class V = typename T::template rebind<U>::other>
    true_type has_rebind_impl(int);

    template <class, class>
    false_type has_rebind_impl(long);

    template <class T, class U>
    struct has_rebind
      : public decltype(has_rebind_impl<T, U>(0))
    {
    };

    template <class T, class U, bool = has_rebind<T, U>::value>
    struct rebind
    {
      using type = typename T::template rebind<U>::other;
    };

    template <template <class, class...> class Ptr, class U, class T, class... Args>
    struct rebind<Ptr<T, Args...>, U, false>
    {
      using type = Ptr<U, Args...>;
    };
  }

  template <class Ptr>
  struct pointer_traits
  {
  public:
    using pointer = Ptr;
    using element_type = typename pointer_traits_detail::element_type<Ptr>::type;
    using difference_type = typename pointer_traits_detail::difference_type<Ptr>::type;

    template <class U>
    struct rebind
    {
      using other = typename pointer_traits_detail::rebind<Ptr, U>::type;
    };

  private:
    using not_void = mpl::if_t<is_void<element_type>, char, element_type>;

  public:
    static pointer pointer_to(not_void& value)
    {
      return Ptr::pointer_to(value);
    }
  };

  template <class T>
  struct pointer_traits<T*>
  {
  public:
    using pointer = T*;
    using element_type = T;
    using difference_type = std::ptrdiff_t;

    template <class U>
    struct rebind
    {
      using other = U*;
    };

  private:
    using not_void = mpl::if_t<is_void<element_type>, char, element_type>;

  public:
    static pointer pointer_to(not_void& value)
    {
      return addressof(value);
    }
  };
}

#endif