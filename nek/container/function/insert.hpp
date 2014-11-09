#ifndef NEK_CONTAINER_FUNCTION_INSERT_HPP
#define NEK_CONTAINER_FUNCTION_INSERT_HPP

#include <initializer_list>

#include <nek/utility/move.hpp>
#include <nek/container/function/emplace_back.hpp>

namespace nek
{
	template <class Container, class Iterator>
	auto insert(Container& con, Iterator first, Iterator last)
	{
		return con.insert(first, last);
	}

	template <class Container, class Iterator>
	auto insert(Container& con, Iterator position, std::initializer_list<typename Container::value_type> list)
	{
		return con.insert(position, list.begin(), list.end());
	}

	template <class Container, class Iterator, class T = typename Container::value_type>
	auto insert(Container& con, Iterator position, T const& value)
	{
		return con.insert(position, static_cast<typename Container::size_type>(1), value);
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