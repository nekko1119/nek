#ifndef NEK_ITERATOR_END_HPP
#define NEK_ITERATOR_END_HPP

#include <cstddef>

namespace nek
{
  template <class Container>
  inline auto end(Container& con) -> decltype(con.end())
  {
    return con.end();
  }

  template <class Container>
  inline auto end(Container const& con) -> decltype(con.end())
  {
    return con.end();
  }

  template <class T, std::size_t N>
  inline T* end(T (&array)[N])
  {
    return array + N;
  }

  template <class Container>
  inline auto cend(Container const& con) -> decltype(con.end())
  {
    return con.end();
  }
}

#endif