#ifndef NEK_ALGORITHM_ROTATE_HPP
#define NEK_ALGORITHM_ROTATE_HPP

#include <nek/algorithm/iter_swap.hpp>
#include <nek/algorithm/reverse.hpp>
#include <nek/iterator/advance.hpp>
#include <nek/iterator/distance.hpp>
#include <nek/iterator/iterator_traits.hpp>

namespace nek
{
  namespace rotate_detail
  {
    /*
    f[12345]m[ABC]l
    [ABC]f[45123]ml
    [ABC]f[45]m[123]l
    [ABC12]f[453]ml
    [ABC12]f[45]m[3]l
    [ABC123]f[54]ml
    [ABCD123]f[5]m[4]l
    [ABCD1234]f[5]ml

    f[123]m[ABCDE]l
    [ABC]f[123]m[DE]l
    [ABCDE]f[312]ml
    [ABCDE]f[3]m[12]l
    [ABCDE1]f[32]ml
    [ABCDE1]f[3]m[2]l
    [ABCDE12]f[3]ml
    */
    template <class ForwardIterator>
    inline void rotate_(ForwardIterator first, ForwardIterator middle, ForwardIterator last, std::forward_iterator_tag)
    {
      if (first == middle || middle == last) {
        return;
      }
      auto current_middle = middle;
      while (current_middle != last) {
        nek::iter_swap(first, current_middle);
        ++first;
        ++current_middle;
        if (first == middle) {
          middle = current_middle;
        } else if (current_middle == last) {
          current_middle = middle;
        }
      }
    }

    template <class BidirectionalIterator>
    inline void rotate_(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, std::bidirectional_iterator_tag)
    {
      if (first == middle || middle == last) {
        return;
      }
      nek::reverse(first, middle);
      nek::reverse(middle, last);
      nek::reverse(first, last);
    }

    template <class RandomAccessIterator>
    inline void rotate_(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, std::random_access_iterator_tag)
    {
      if (first == middle || middle == last) {
        return;
      }
      // TODO : gcd
      using diff_type = typename nek::iterator_traits<RandomAccessIterator>::difference_type;
      auto shift = middle - first;
      auto count = last - first;
      diff_type temp;
      while (shift != 0) {
        temp = shift;
        shift = count % shift;
        count = temp;
      }
      diff_type repeat = count;
      for (auto i = 0; i < repeat; ++i) {
        for (diff_type cursor = i, next; (next = (cursor + (middle - first)) % (last - first)) != i; cursor = next) {
          nek::iter_swap(first + cursor , first + next);
        }
      }
    }
  }

  // see : http://www.kmonos.net/wlog/115.html#_0007101223
  template <class ForwardIterator>
  ForwardIterator rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last)
  {
    using tag = typename nek::iterator_traits<ForwardIterator>::iterator_category;
    rotate_detail::rotate_(first, middle, last, tag{});
    nek::advance(first, nek::distance(middle, last));
    return first;
  }
}

#endif