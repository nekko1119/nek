#ifndef NEK_CONTAINER_FUNCTION_ERASE_HPP
#define NEK_CONTAINER_FUNCTION_ERASE_HPP

#include <iterator> // TODO : std::prev

namespace nek
{
	template <class Container, class Iterator>
	auto erase(Container& con, Iterator first, Iterator last)
	{
		return con.erase(first, last);
	}

	template <class Container, class Iterator>
	auto erase(Container& con, Iterator position)
	{
		return con.erase(std::prev(position), position);
	}
}

#endif
