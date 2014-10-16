#ifndef NEK_TYPE_TRAITS_IS_VOID_HPP
#define NEK_TYPE_TRAITS_IS_VOID_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
	namespace is_void_detail
	{
		template <class T>
		struct is_void
			: public false_type
		{
		};

		template <>
		struct is_void<void>
			: public true_type
		{
		};
	}

	template <class T>
	struct is_void
		: public is_void_detail::is_void<remove_cv_t<T>>
	{
	};
}

#endif