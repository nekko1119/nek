#ifndef NEK_CONTAINER_FUNCTION_AT_HPP
#define NEK_CONTAINER_FUNCTION_AT_HPP

#include <stdexcept>

#include <nek/container/function/size.hpp>

namespace nek
{
	template <class Container, class Size>
	decltype(auto) at(Container& con, Size n)
	{
		using size_type = typename Container::size_type;
		if (nek::size(con) < static_cast<size_type>(n)) {
			throw std::out_of_range{"nek::at"};
		}
		return con[n];
	}

	template <class Container, class Size>
	decltype(auto) at(Container const& con, Size n)
	{
		using size_type = typename Container::size_type;
		if (nek::size(con) < static_cast<size_type>(n)) {
			throw std::out_of_range{"nek::at"};
		}
		return con[n];
	}

	template <class Container, class Size>
	decltype(auto) cat(Container const& con, Size n)
	{
		using size_type = typename Container::size_type;
		if (nek::size(con) < static_cast<size_type>(n)) {
			throw std::out_of_range{"nek::at"};
		}
		return con[n];
	}
}

#endif