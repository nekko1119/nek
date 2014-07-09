#ifndef NEK_DETAIL_CONSTRUCT_HPP
#define NEK_DETAIL_CONSTRUCT_HPP

#include <new>
#include <nek/utility/forward.hpp>

namespace nek
{
  namespace detail
  {
    template <class T, class... Args>
    inline void construct(T* ptr, Args&&... args)
    {
      ::new (static_cast<void*>(ptr)) T(nek::forward<Args>(args)...);
    }
  }
}

#endif