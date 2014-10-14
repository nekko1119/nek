#ifndef NEK_ALGORITHM_COPY_HPP
#define NEK_ALGORITHM_COPY_HPP

#include <cstring>
#include <nek/iterator/iterator_traits.hpp>
#include <nek/iterator/move_iterator.hpp>
#include <nek/type_traits/is_pointer.hpp>
#include <nek/type_traits/is_same.hpp>
#include <nek/type_traits/is_trivial.hpp>
#include <nek/utility/addressof.hpp>
#include <nek/utility/move.hpp> 

namespace nek
{
	namespace copy_detail
	{

		template <class IsMoveIterator, class IsMemmovable, class Tag>
		struct copy_
		{
			template <class InputIterator, class OutputIterator>
			static OutputIterator copy(InputIterator first, InputIterator last, OutputIterator dest)
			{
				for (; first != last; ++first, ++dest) {
					*dest = *first;
				}
				return dest;
			}
		};

		template <class Tag>
		struct copy_<nek::true_type, nek::false_type, Tag>
		{
			template <class InputIterator, class OutputIterator>
			static OutputIterator copy(InputIterator first, InputIterator last, OutputIterator dest)
			{
				for (; first != last; ++first, ++dest) {
					*dest = nek::move(*first);
				}
				return dest;
			}
		};

		template <class IsMoveIterator>
		struct copy_<IsMoveIterator, nek::true_type, std::random_access_iterator_tag>
		{
			template <class InputIterator, class OutputIterator>
			static OutputIterator copy(InputIterator first, InputIterator last, OutputIterator dest)
			{
				auto const count = last - first;
				if (count) {
					std::memmove(addressof(*dest), addressof(*first), count * sizeof(*first));
				}
				return dest + count;
			}
		};

		template <class IsMoveIterator, class InputIterator, class OutputIterator>
		OutputIterator copy(InputIterator first, InputIterator last, OutputIterator dest)
		{
			using in_value_type = typename iterator_traits<InputIterator>::value_type;
			using out_value_type = typename iterator_traits<OutputIterator>::value_type;
			using iterator_category = typename iterator_traits<InputIterator>::iterator_category;
			using is_memmovable = nek::integral_constant<bool, mpl::and_<
				nek::is_trivial<in_value_type>,
				nek::is_pointer<InputIterator>,
				nek::is_pointer<OutputIterator>,
				nek::is_same<in_value_type, out_value_type>>::value>;

			return copy_detail::copy_<
				IsMoveIterator, is_memmovable, iterator_category>::copy(first, last, dest);
		}
	}

	template <class InputIterator, class OutputIterator>
	OutputIterator copy(InputIterator first, InputIterator last, OutputIterator dest)
	{
		return copy_detail::copy<is_move_iterator<InputIterator>>(first, last, dest);
	}
}

#endif