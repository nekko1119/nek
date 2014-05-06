#ifndef NEK_MPL_IDENTITY_HPP
#define NEK_MPL_IDENTITY_HPP

namespace nek
{
  namespace mpl
  {
    template <class T>
    struct identity
    {
      using type = T;
    };

    template <class T>
    using identity_t = typename identity<T>::type;
  }
}

#endif