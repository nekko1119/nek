﻿#ifndef NEK_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP
#define NEK_TYPE_TRAITS_IS_RVALUE_REFERENCE_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
	namespace detail
	{
		template <class T>
		struct is_rvalue_reference
			: public false_type
		{
		};

		template <class T>
		struct is_rvalue_reference<T&&>
			: public true_type
		{
		};
	}

	template <class T>
	struct is_rvalue_reference
		: public detail::is_rvalue_reference<typename remove_cv<T>::type>
	{
	};
}

#endif