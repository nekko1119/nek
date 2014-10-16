#ifndef NEK_TYPE_TRAITS_REMOVE_EXTENDS_HPP
#define NEK_TYPE_TRAITS_REMOVE_EXTENDS_HPP

#include <cstddef>

namespace nek
{
	template <class T>
	struct remove_extends
	{
		using type = T;
	};

	template <class T>
	struct remove_extends<T[]>
	{
		using type = T;
	};

	template <class T, std::size_t N>
	struct remove_extends<T[N]>
	{
		using type = T;
	};

	template <class T>
	using remove_extends_t = typename remove_extends<T>::type;

}

#endif