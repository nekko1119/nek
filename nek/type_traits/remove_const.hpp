#ifndef NEK_TYPE_TRAITS_REMOVE_CONST_HPP
#define NEK_TYPE_TRAITS_REMOVE_CONST_HPP

namespace nek
{
  template <class T>
  struct remove_const
  {
    using type = T;
  };

  template <class T>
  struct remove_const<T const>
  {
    using type = T;
  };

  template <class T>
  using remove_const_t = typename remove_const<T>::type;
}

#endif