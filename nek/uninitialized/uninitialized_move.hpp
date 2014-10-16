#ifndef NEK_UNINITIALIZED_MOVE_HPP
#define NEK_UNINITIALIZED_MOVE_HPP

#include <nek/iterator/move_iterator.hpp>
#include <nek/uninitialized/uninitialized_copy.hpp>

namespace nek
{
	template <class InputIterator, class ForwardIterator>
	ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator dest)
	{
		return nek::uninitialized_copy(nek::make_move_iterator(first), nek::make_move_iterator(last), dest);
	}

	template <class InputIterator, class ForwardIterator, class Allocator>
	ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator dest, Allocator& allocator)
	{
		return nek::uninitialized_copy(nek::make_move_iterator(first), nek::make_move_iterator(last), dest, allocator);
	}
}

#endif