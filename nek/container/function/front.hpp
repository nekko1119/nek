#ifndef NEK_CONTAINER_FUNCTION_FRONT_HPP
#define NEK_CONTAINER_FUNCTION_FRONT_HPP

#include <cstddef>

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

	template <class T, std::size_t N>
	constexpr decltype(auto) front(T(&array)[N])
	{
		return array[0];
	}

	template <class T, std::size_t N>
	constexpr decltype(auto) front(T const (&array)[N])
	{
		return array[0];
	}
}

#endif