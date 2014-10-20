#ifndef NEK_ALGORITHM_MOVE_HPP
#define NEK_ALGORITHM_MOVE_HPP

#include <cstring>
#include <nek/iterator/iterator_traits.hpp>
#include <nek/mpl/and.hpp>
#include <nek/type_traits/is_pointer.hpp>
#include <nek/type_traits/is_same.hpp>
#include <nek/type_traits/is_trivial.hpp>
#include <nek/utility/addressof.hpp>
#include <nek/utility/move.hpp>

namespace nek
{
	namespace move_detail
	{
		template <class IsMemmovable>
		struct move_
		{
			template <class InputIterator, class OutputIterator>
			static OutputIterator move(InputIterator first, InputIterator last, OutputIterator dest)
			{
				for (; first != last; ++first, ++dest) {
					*dest = nek::move(*first);
				}
				return dest;
			}
		};

		template <>
		struct move_<nek::false_type>
		{
			template <class InputIterator, class OutputIterator>
			static OutputIterator move(InputIterator first, InputIterator last, OutputIterator dest)
			{
				auto const count = last - first;
				if (count) {
					std::memmove(addressof(*dest), addressof(*first), count * sizeof(*first));
				}
				return dest + count;
			}
		};

		template <class InputIterator, class OutputIterator>
		OutputIterator move(InputIterator first, InputIterator last, OutputIterator dest)
		{
			using in_value_type = typename iterator_traits<InputIterator>::value_type;
			using out_value_type = typename iterator_traits<OutputIterator>::value_type;
			using is_memmovable = nek::integral_constant<bool, mpl::and_<
				nek::is_trivial<in_value_type>,
				nek::is_pointer<InputIterator>,
				nek::is_pointer<OutputIterator>,
				nek::is_same<in_value_type, out_value_type>>::value>;

			return move_detail::move_<is_memmovable>::move(first, last, dest);
		}
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator move(InputIterator first, InputIterator last, OutputIterator dest)
	{
		return move_detail::move(first, last, dest);
	}
}

#endif