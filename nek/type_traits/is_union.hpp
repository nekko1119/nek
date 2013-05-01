#ifndef NEK_TYPE_TRAITS_IS_UNION_HPP
#define NEK_TYPE_TRAITS_IS_UNION_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
	template <class T>
	struct is_union
		: public integral_constant<bool, __is_union(typename remove_cv<T>::type)>
	{
	};
}

#endif