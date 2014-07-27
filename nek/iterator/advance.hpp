#ifndef NEK_ITERATOR_ADVANCE_HPP
#define NEK_ITERATOR_ADVANCE_HPP

#include <cassert>
#include <nek/iterator/iterator_traits.hpp>

namespace nek
{
  namespace advance_detail
  {
    template <class InputIterator, class Difference>
    inline void advance_(InputIterator& it, Difference diff, nek::input_iterator_tag)
    {
      assert(0 < diff && "nek::advance: it is inupt iterator, so diff must be more larger than 0.");
      for (; 0 < diff; --diff) {
        ++it;
      }
    }

    template <class ForwardIterator, class Difference>
    inline void advance_(ForwardIterator& it, Difference diff, nek::forward_iterator_tag)
    {
      assert(0 < diff && "nek::advance: it is inupt iterator, so diff must be more larger than 0.");
      for (; 0 < diff; --diff) {
        ++it;
      }
    }

    template <class BidirectionalIterator, class Difference>
    inline void advance_(BidirectionalIterator& it, Difference diff, nek::bidirectional_iterator_tag)
    {
      if (0 < diff) {
        for (; 0 < diff; --diff) {
          ++it;
        }
      } else {
        for (; diff < 0; ++diff) {
          --it;
        }
      }
    }

    template <class RandomAccessIterator, class Difference>
    inline void advance_(RandomAccessIterator& it, Difference diff, nek::random_access_iterator_tag)
    {
      it += diff;
    }
  }

  template <class InputIterator, class Difference>
  inline void advance(InputIterator& it, Difference diff)
  {
    using tag = typename nek::iterator_traits<InputIterator>::iterator_category;
    advance_detail::advance_(it, diff, tag{});
  }
}

#endif