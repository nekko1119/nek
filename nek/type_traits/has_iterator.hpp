#ifndef NEK_TYPE_TRAITS_HAS_ITERATOR_HPP
#define NEK_TYPE_TRAITS_HAS_ITERATOR_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
	namespace has_iterator_detail
	{
		template <class T, class U = T::iterator>
		true_type has_iterator(int);

		template <class>
		false_type has_iterator(long);
	}

	template <class T>
	struct has_iterator
		: public decltype(has_iterator_detail::has_iterator<T>(0))
	{
	};
}

#endif