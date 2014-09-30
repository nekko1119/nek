#ifndef NEK_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP
#define NEK_TYPE_TRAITS_IS_CONSTRUCTIBLE_HPP

#include <type_traits> // TODO : std::is_function, std::destructible

#include <nek/mpl/and.hpp>
#include <nek/mpl/if.hpp>
#include <nek/mpl/not.hpp>
#include <nek/mpl/or.hpp>
#include <nek/type_traits/is_base_of.hpp>
#include <nek/type_traits/is_lvalue_reference.hpp>
#include <nek/type_traits/is_reference.hpp>
#include <nek/type_traits/is_rvalue_reference.hpp>
#include <nek/type_traits/is_default_construdtible.hpp>
#include <nek/type_traits/is_same.hpp>
#include <nek/type_traits/is_static_castable.hpp>
#include <nek/type_traits/is_void.hpp>
#include <nek/type_traits/remove_cv.hpp>
#include <nek/type_traits/remove_reference.hpp>
#include <nek/utility/declval.hpp>

#include <boost/mpl/print.hpp>
#include <boost/mpl/vector.hpp>
namespace nek
{
  namespace is_constructible_detail
  {
    template <class From, class To>
    struct is_l_ref_to_r_ref_impl
    {
    private:
      using from_type = nek::remove_cv_t<nek::remove_reference_t<From>>;
      using to_type = nek::remove_cv_t<nek::remove_reference_t<To>>;

    public:
      using type =
        mpl::and_<
          mpl::not_<std::is_function<from_type>>,
          mpl::or_<
            nek::is_same<from_type, to_type>,
            nek::is_base_of<to_type, from_type>
          >
        >;
    };

    template <class From, class To, bool = mpl::and_<nek::is_lvalue_reference<From>, nek::is_rvalue_reference<To>>::value>
    struct is_l_ref_to_r_ref
      : public is_l_ref_to_r_ref_impl<From, To>::type
    {
    };

    template <class From, class To>
    struct is_l_ref_to_r_ref<From, To, false>
      : public nek::false_type
    {
    };

    template <class Base, class Derived>
    struct is_base_to_derived_ref_impl
    {
    private:
      using base_type = nek::remove_cv_t<nek::remove_reference_t<Base>>;
      using derived_type = nek::remove_cv_t<nek::remove_reference_t<Derived>>;

    public:
      using type =
        mpl::and_<
          mpl::not_<nek::is_same<base_type, derived_type>>,
          nek::is_base_of<base_type, derived_type>
        >;
    };

    template <class Base, class Derived, bool = mpl::not_<mpl::or_<nek::is_void<Base>, std::is_function<Base>>>::value>
    struct is_base_to_derived_ref
      : public is_base_to_derived_ref_impl<Base, Derived>::type
    {
    };

    template <class Base, class Derived>
    struct is_base_to_derived_ref<Base, Derived, false>
      : public nek::false_type
    {
    };

    template <class T, class Arg>
    struct is_direct_constructible_ref
      : public mpl::and_<
          nek::is_static_castable<T, Arg>,
          mpl::not_<mpl::or_<
            is_base_to_derived_ref<Arg, T>,
            is_l_ref_to_r_ref<Arg, T>
          >>
        >
    {
    };

    template <class T, class Arg>
    struct is_able_to_placement_new_impl
    {
    private:
      template <class T2, class Arg2, class = decltype(::new T2(nek::declval<Arg>()))>
      static nek::true_type check(int);

      template <class, class>
      static nek::false_type check(long);

    public:
      using type = decltype(check<T, Arg>(0));
    };

    template <class From, class To>
    struct is_able_to_placement_new
      : public mpl::and_<std::is_destructible<From>, typename is_able_to_placement_new_impl<From, To>::type>::type
    {
    };

    template <class T, class Arg>
    struct is_direct_cosntructible
      : public mpl::if_t<nek::is_reference<T>,
          is_direct_constructible_ref<T, Arg>,
          is_able_to_placement_new<T, Arg>>
    {
    };

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

    template <class T, class Arg>
    struct is_constructible_<T, Arg>
      : public nek::integral_constant<bool, is_direct_cosntructible<T, Arg>::value>
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