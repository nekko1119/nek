#ifndef NEK_ITERATOR_BEGIN_HPP
#define NEK_ITERATOR_BEGIN_HPP

#include <cstddef>

namespace nek
{
  template <class Container>
  inline auto begin(Container& con) -> decltype(con.begin())
  {
    return con.begin();
  }

  template <class Container>
  inline auto begin(Container const& con) -> decltype(con.begin())
  {
    return con.begin();
  }

  template <class T, std::size_t N>
  inline T* begin(T (&array)[N])
  {
    return array;
  }

  template <class Container>
  inline auto cbegin(Container const& con) -> decltype(con.begin())
  {
    return con.begin();
  }
}

#endif