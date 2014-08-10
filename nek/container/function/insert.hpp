#ifndef NEK_CONTAINER_FUNCTION_INSERT_HPP
#define NEK_CONTAINER_FUNCTION_INSERT_HPP

#include <initializer_list>

#include <algorithm> // TODO std::fill_n
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

  template <class Container, class Iterator, class Size, class Value>
  auto insert(Container& v, Iterator position, Size count, Value const& value)
  {
    if (count == 0) {
      return position;
    }

    nek::vector<Value> temp(count);
    std::fill_n(temp.begin(), count, value);
    return v.insert(position, temp.begin(), temp.end());
  }
}

#endif