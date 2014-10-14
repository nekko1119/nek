#ifndef NEK_ALGORITHM_FILL_HPP
#define NEK_ALGORITHM_FILL_HPP

#include <cstring>

#include <nek/type_traits/is_byte.hpp>
#include <nek/type_traits/enable_if.hpp>

namespace nek
{
	namespace fill_detail
	{
		template <class ForwardIterator, class T>
		inline nek::disable_if_t<is_byte<T>> fill_(ForwardIterator first, ForwardIterator last, T const& value)
		{
			for (; first != last; ++first) {
				*first = value;
			}
		}

		template <class T>
		inline nek::enable_if_t<is_byte<T>> fill_(T* first, T* last, T const& value)
		{
			std::memset(first, value, last - first);
		}
	}

	template <class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, T const& value)
	{
		fill_detail::fill_(first, last, value);
	}
}

#endif