#ifndef NEK_TYPE_TRAITS_REMOVE_VOLATILE_HPP
#define NEK_TYPE_TRAITS_REMOVE_VOLATILE_HPP

namespace nek
{
	template <class T>
	struct remove_volatile
	{
		typedef T type;
	};

	template <class T>
	struct remove_volatile<volatile T>
	{
		typedef T type;
	};
}

#endif