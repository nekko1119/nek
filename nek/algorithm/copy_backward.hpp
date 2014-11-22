#ifndef NEK_ALGORITHM_COPY_BACKWARD_HPP
#define NEK_ALGORITHM_COPY_BACKWARD_HPP

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
    namespace copy_backward_detail
    {

        template <class IsMoveIterator, class IsMemmovable, class Tag>
        struct copy_backward
        {
            template <class BidirectionalIterator1, class BidirectionalIterator2>
            static BidirectionalIterator2 copy_backward_(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 dest)
            {
                while (first != last) {
                    *(--dest) = *(--last);
                }
                return dest;
            }
        };

        template <class Tag>
        struct copy_backward<nek::true_type, nek::false_type, Tag>
        {
            template <class BidirectionalIterator1, class BidirectionalIterator2>
            static BidirectionalIterator2 copy_backward_(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 dest)
            {
                while (first != last) {
                    *(--dest) = nek::move(*(--last));
                }
                return dest;
            }
        };

        template <class IsMoveIterator>
        struct copy_backward<IsMoveIterator, nek::true_type, std::random_access_iterator_tag>
        {
            template <class BidirectionalIterator1, class BidirectionalIterator2>
            static BidirectionalIterator2 copy_backward_(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 dest)
            {
                auto const count = last - first;
                if (count) {
                    std::memmove(addressof(*dest) - count, addressof(*first), count * sizeof(*first));
                }
                return dest - count;
            }
        };

        template <class IsMoveIterator, class BidirectionalIterator1, class BidirectionalIterator2>
        BidirectionalIterator2 copy_backward_(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 dest)
        {
            using in_value_type = typename iterator_traits<BidirectionalIterator1>::value_type;
            using out_value_type = typename iterator_traits<BidirectionalIterator2>::value_type;
            using iterator_category = typename iterator_traits<BidirectionalIterator1>::iterator_category;
            using is_memmovable = nek::integral_constant<bool, mpl::and_<
                nek::is_trivial<in_value_type>,
                nek::is_pointer<BidirectionalIterator1>,
                nek::is_pointer<BidirectionalIterator2>,
                nek::is_same<in_value_type, out_value_type>>::value>;

            return copy_backward_detail::copy_backward<
                IsMoveIterator, is_memmovable, iterator_category>::copy_backward_(first, last, dest);
        }
    }

    template <class BidirectionalIterator1, class BidirectionalIterator2>
    BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 dest)
    {
        return copy_backward_detail::copy_backward_<is_move_iterator<BidirectionalIterator1>>(first, last, dest);
    }
}

#endif