#ifndef NEK_ALGORITHM_REVERSE_HPP
#define NEK_ALGORITHM_REVERSE_HPP

#include <nek/algorithm/iter_swap.hpp>

namespace nek
{
	template <class BidirectionalIterator>
	inline void reverse(BidirectionalIterator first, BidirectionalIterator last)
	{
		for (; first != last && first != --last; ++first) {
			nek::iter_swap(first, last);
		}
	}
}

#endif