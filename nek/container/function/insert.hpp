#ifndef NEK_CONTAINER_FUNCTION_INSERT_HPP
#define NEK_CONTAINER_FUNCTION_INSERT_HPP

#include <initializer_list>

#include <nek/algorithm/fill_n.hpp>
#include <nek/container/container_fwd.hpp>
#include <nek/container/function/emplace_back.hpp>
#include <nek/utility/move.hpp>

namespace nek
{
  template <class Container, class Iterator>
  auto insert(Container& con, Iterator position, std::initializer_list<typename Container::value_type> list)
  {
    return con.insert(position, list.begin(), list.end());
  }

  template <class Container, class Iterator, class Value>
  auto insert(Container& con, Iterator position, Value const& value)
  {
    return nek::insert(con, position, {value});
  }

  template <class Container, class Iterator, class Value>
  auto insert(Container& con, Iterator position, Value&& value)
  {
    return nek::emplace_back(con, nek::move(value));
  }

  template <class Container>
  auto insert(Container& con, typename Container::iterator position, typename Container::size_type count, typename Container::value_type const& value)
  {
    return con.insert(position, count, value);
  }
}

#endif