#ifndef NEK_TYPE_TRAITS_REMOVE_VOLATILE_HPP
#define NEK_TYPE_TRAITS_REMOVE_VOLATILE_HPP

#include <cstddef>

namespace nek
{
  template <class T>
  struct remove_volatile
  {
    using type = T;
  };

  template <class T>
  struct remove_volatile<T volatile>
  {
    using type = T;
  };


  // workaround Visual C++
  template <class T>
  struct remove_volatile<T volatile[]>
  {
    using type = T[];
  };

  template <class T, std::size_t N>
  struct remove_volatile<T volatile[N]>
  {
    using type = T[N];
  };

  template <class T>
  using remove_volatile_t = typename remove_volatile<T>::type;
}

#endif