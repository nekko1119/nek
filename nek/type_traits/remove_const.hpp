#ifndef NEK_TYPE_TRAITS_REMOVE_CONST_HPP
#define NEK_TYPE_TRAITS_REMOVE_CONST_HPP

#include <cstddef>

namespace nek
{
	template <class T>
	struct remove_const
	{
		using type = T;
	};

	template <class T>
	struct remove_const<T const>
	{
		using type = T;
	};

	// workaround Visual C++
	template <class T>
	struct remove_const<T const[]>
	{
		using type = T[];
	};

	template <class T, std::size_t N>
	struct remove_const<T const[N]>
	{
		using type = T[N];
	};

	template <class T>
	using remove_const_t = typename remove_const<T>::type;
}

#endif