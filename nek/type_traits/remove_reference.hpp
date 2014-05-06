#ifndef NEK_REMOVE_REFERENCE_HPP
#define NEK_REMOVE_REFERENCE_HPP

namespace nek
{
  template <class T>
  struct remove_reference
  {
    using type = T;
  };

  template <class T>
  struct remove_reference<T&>
  {
    using type = T;
  };

  template <class T>
  struct remove_reference<T&&>
  {
    using type = T;
  };

  template <class T>
  using remove_reference_t = typename remove_reference<T>::type;
}

#endif