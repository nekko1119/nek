#ifndef NEK_MPL_OR_HPP
#define NEK_MPL_OR_HPP

#include <nek/mpl/bool.hpp>
#include <boost/mpl/or.hpp>

namespace nek
{
	namespace mpl
	{
		namespace or_detail
		{
			template <bool...>
			struct or_c_impl
				: public true_
			{
			};

			template <>
			struct or_c_impl<false>
				: public false_
			{
			};

			template <bool... Cs>
			struct or_c_impl<false, Cs...>
				: public or_c_impl<Cs...>
			{
			};

			template <bool, class...>
			struct or_impl
				: public true_
			{
			};

			template <>
			struct or_impl<false>
				: public false_
			{
			};

			template <class T, class... Ts>
			struct or_impl<false, T, Ts...>
				: public or_impl<T::type::value, Ts...>
			{
			};
		}

		template <bool... Cs>
		struct or_c
			: public or_detail::or_c_impl<Cs...>
		{
		};

		template <class T, class... Ts>
		struct or_
			: public or_detail::or_impl<T::type::value, Ts...>
		{
		};
	}
}

#endif