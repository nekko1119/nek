#ifndef NEK_TYPE_TRAITS_REMOVE_CV_HPP
#define NEK_TYPE_TRAITS_REMOVE_CV_HPP

#include <nek/type_traits/remove_const.hpp>
#include <nek/type_traits/remove_volatile.hpp>

namespace nek
{
	template <class T>
	struct remove_cv
	{
		typedef typename remove_const<typename remove_volatile<T>::type>::type type;
	};
}

#endif