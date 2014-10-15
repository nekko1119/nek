#ifndef NEK_ITERATOR_BEGIN_HPP
#define NEK_ITERATOR_BEGIN_HPP

#include <cstddef>
#include <nek/iterator/reverse_iterator.hpp>

namespace nek
{
	template <class Container>
	inline auto begin(Container& con) -> decltype(con.begin())
	{
		return con.begin();
	}

	template <class Container>
	inline auto begin(Container const& con) -> decltype(con.begin())
	{
		return con.begin();
	}

	template <class T, std::size_t N>
	inline T* begin(T (&array)[N])
	{
		return array;
	}

	template <class Container>
	inline auto cbegin(Container const& con) -> decltype(con.begin())
	{
		return con.begin();
	}

	template <class T, std::size_t N>
	inline T const* cbegin(T const (&array)[N])
	{
		return array;
	}

	template <class Container>
	inline auto rbegin(Container& con) -> decltype(con.rbegin())
	{
		return con.rbegin();
	}

	template <class Container>
	inline auto rbegin(Container const& con) -> decltype(con.rbegin())
	{
		return con.rbegin();
	}

	template <class T, std::size_t N>
	inline nek::reverse_iterator<T*> rbegin(T(&array)[N])
	{
		return nek::reverse_iterator<T*>{array + N};
	}

	template <class Container>
	inline auto crbegin(Container const& con) -> decltype(con.rbegin())
	{
		return con.rbegin();
	}

	template <class T, std::size_t N>
	inline nek::reverse_iterator<T const*> crbegin(T const (&array)[N])
	{
		return nek::reverse_iterator<T const*>{array + N};
	}
}

#endif