#ifndef NEK_CONTAINER_FUNCTION_FRONT_HPP
#define NEK_CONTAINER_FUNCTION_FRONT_HPP

namespace nek
{
  template <class Container>
  decltype(auto) front(Container& con)
  {
    return *con.begin();
  }

  template <class Container>
  decltype(auto) front(Container const& con)
  {
    return *con.begin();
  }
}

#endif