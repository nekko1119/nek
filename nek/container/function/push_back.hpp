#ifndef NEK_CONTAINER_FUNCTION_PUSH_BACK_HPP
#define NEK_CONTAINER_FUNCTION_PUSH_BACK_HPP

#include <nek/container/function/emplace_back.hpp>
#include <nek/container/function/insert.hpp>
#include <nek/type_traits/remove_reference.hpp>
#include <nek/utility/move.hpp>

namespace nek
{
	template <class Container, class Value>
	void push_back(Container& con, Value const& value)
	{
		nek::insert(con, con.end(), value);
	}

	template <class Container, class Value>
	void push_back(Container& con, nek::remove_reference_t<Value>&& value)
	{
		nek::emplace_back(con, nek::move(value));
	}
}

#endif