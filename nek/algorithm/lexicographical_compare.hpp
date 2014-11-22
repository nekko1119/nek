#ifndef NEK_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP
#define NEK_ALGORITHM_LEXICOGRAPHICAL_COMPARE_HPP

#include <cstddef>
#include <cstring>

#include <nek/algorithm/min.hpp>
#include <nek/iterator/iterator_traits.hpp>
#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/is_byte.hpp>
#include <nek/type_traits/is_integral.hpp>
#include <nek/type_traits/is_pointer.hpp>
#include <nek/type_traits/is_same.hpp>
#include <nek/type_traits/is_signed.hpp>

namespace nek
{
    namespace lexicographical_compare_detail
    {
        template <class InputIterator1, class InputIterator2>
        bool lexicographical_compare_(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, nek::false_type)
        {
            for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
                if (*first1 < *first2) {
                    return true;
                } else if (*first2 < *first1) {
                    return false;
                }
            }
            return first1 == last1 && first2 != last2;
        }

        template <class T>
        bool lexicographical_compare_(T const* first1, T const* last1, T const* first2, T const* last2, nek::true_type)
        {
            std::ptrdiff_t const length1 = last1 - first1;
            std::ptrdiff_t const length2 = last2 - first2;
            int const result = std::memcmp(first1, first2, nek::min(length1, length2));
            return result != 0 ? result < 0 : length1 < length2;
        }
    }

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
    {
        using value_type1 = typename nek::iterator_traits<InputIterator1>::value_type;
        using value_type2 = typename nek::iterator_traits<InputIterator2>::value_type;

        using is_byte_comparable = nek::integral_constant<bool,
            nek::is_pointer<InputIterator1>::value &&
            nek::is_byte<value_type1>::value && nek::is_signed<value_type1>::value &&
            nek::is_same<InputIterator1, InputIterator2>::value>;
        return lexicographical_compare_detail::lexicographical_compare_(first1, last1, first2, last2, is_byte_comparable{});
    }

    template <class InputIterator1, class InputIterator2, class Predicate>
    bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Predicate pred)
    {
        for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
            if (pred(*first1, *first2)) {
                return true;
            } else if (pred(*first2, *first1)) {
                return false;
            }
        }
        return first1 == last1 && first2 != last2;
    }
}

#endif