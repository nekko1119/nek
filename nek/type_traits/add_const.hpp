#ifndef NEK_TYPE_TRAITS_ADD_CONST_HPP
#define NEK_TYPE_TRAITS_ADD_CONST_HPP

namespace nek
{
  template <class T>
  struct add_const
  {
    using type = T const;
  };

  template <class T>
  using add_const_t = typename add_const<T>::type;
}

#endif