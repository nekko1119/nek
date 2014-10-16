#ifndef NEK_TYPE_TRAITS_IS_LVALUE_REFERENCE_HPP
#define NEK_TYPE_TRAITS_IS_LVALUE_REFERENCE_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
	namespace is_lvalue_reference_detail
	{
		template <class T>
		struct is_lvalue_reference
			: public false_type
		{
		};

		template <class T>
		struct is_lvalue_reference<T&>
			: public true_type
		{
		};
	}

	template <class T>
	struct is_lvalue_reference
		: public is_lvalue_reference_detail::is_lvalue_reference<remove_cv_t<T>>
	{
	};
}

#endif