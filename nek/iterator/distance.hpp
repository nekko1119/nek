#ifndef NEK_ITERATOR_DISTANCE_HPP
#define NEK_ITERATOR_DISTANCE_HPP

#include <nek/iterator/iterator_traits.hpp>

namespace nek
{
    namespace distance_detail
    {
        template <class Difference, class InputIterator>
        Difference distance_(InputIterator first, InputIterator last, std::input_iterator_tag)
        {
            Difference diff = static_cast<Difference>(0);
            for (; first != last; ++first) {
                ++diff;
            }
            return diff;
        }

        template <class Difference, class RandomAccessIterator>
        Difference distance_(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
        {
            return static_cast<Difference>(last - first);
        }
    }

    template <class InputIterator>
    auto distance(InputIterator first, InputIterator last)
    {
        using diff_type = typename nek::iterator_traits<InputIterator>::difference_type;
        using tag = typename nek::iterator_traits<InputIterator>::iterator_category;
        return distance_detail::distance_<diff_type>(first, last, tag{});
    }
}

#endif
