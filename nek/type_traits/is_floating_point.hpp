#ifndef NEK_TYPE_TRAITS_IS_FLOATING_POINT_HPP
#define NEK_TYPE_TRAITS_IS_FLOATING_POINT_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>

namespace nek
{
	namespace is_floating_point_detail
	{
		template <class T>
		struct is_floating_point
			: public false_type
		{
		};

		template <>
		struct is_floating_point<float>
			: public true_type
		{
		};

		template <>
		struct is_floating_point<double>
			: public true_type
		{
		};

		template <>
		struct is_floating_point<long double>
			: public true_type
		{
		};
	}

	template <class T>
	struct is_floating_point
		: public is_floating_point_detail::is_floating_point<remove_cv_t<T>>
	{
	};
}
#endif