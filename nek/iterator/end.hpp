#ifndef NEK_ITERATOR_END_HPP
#define NEK_ITERATOR_END_HPP

#include <cstddef>
#include <nek/iterator/reverse_iterator.hpp>

namespace nek
{
	template <class Container>
	inline auto end(Container& con) -> decltype(con.end())
	{
		return con.end();
	}

	template <class Container>
	inline auto end(Container const& con) -> decltype(con.end())
	{
		return con.end();
	}

	template <class T, std::size_t N>
	inline T* end(T (&array)[N])
	{
		return array + N;
	}

	template <class Container>
	inline auto cend(Container const& con) -> decltype(con.end())
	{
		return con.end();
	}

	template <class T, std::size_t N>
	inline T const* cend(T const (&array)[N])
	{
		return array + N;
	}

	template <class Container>
	inline auto rend(Container& con) -> decltype(con.rend())
	{
		return con.rend();
	}

	template <class Container>
	inline auto rend(Container const& con) -> decltype(con.rend())
	{
		return con.rend();
	}

	template <class T, std::size_t N>
	inline nek::reverse_iterator<T*> rend(T(&array)[N])
	{
		return nek::reverse_iterator<T*>{array};
	}

	template <class Container>
	inline auto crend(Container const& con) -> decltype(con.rend())
	{
		return con.rend();
	}

	template <class T, std::size_t N>
	inline nek::reverse_iterator<T const*> crend(T const (&array)[N])
	{
		return nek::reverse_iterator<T const*>{array};
	}
}

#endif