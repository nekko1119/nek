#ifndef NEK_CONTAINER_FUNCTION_CLEAR_HPP
#define NEK_CONTAINER_FUNCTION_CLEAR_HPP

namespace nek
{
  template <class Container>
  void clear(Container& con)
  {
    con.erase(con.begin(), con.end());
  }
}

#endif