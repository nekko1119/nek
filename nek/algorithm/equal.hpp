#ifndef NEK_ALGORITHM_EQUAL_HPP
#define NEK_ALGORITHM_EQUAL_HPP

#include <cstring>
#include <nek/iterator/iterator_traits.hpp>
#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/is_byte.hpp>
#include <nek/type_traits/is_integral.hpp>
#include <nek/type_traits/is_pointer.hpp>
#include <nek/type_traits/is_same.hpp>

namespace nek
{
    namespace equal_detail
    {
        template <class InputIterator1, class InputIterator2>
        bool equal_(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, nek::false_type)
        {
            for (; first1 != last1; ++first1, ++first2) {
                if (!(*first1 == *first2)) {
                    return false;
                }
            }
            return true;
        }

        template <class T>
        inline bool equal_(T const* first1, T const* last1, T const* first2, nek::true_type)
        {
            return std::memcmp(first1, first2, sizeof(T) * (last1 - first1)) == 0;
        }
    }

    template <class InputIterator1, class InputIterator2>
    inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
    {
        using value_type1 = typename nek::iterator_traits<InputIterator1>::value_type;
        using value_type2 = typename nek::iterator_traits<InputIterator2>::value_type;
        using is_byte_comparable_type = nek::integral_constant<bool,
            (nek::is_byte<value_type1>::value || nek::is_pointer<value_type1>::value)
            && nek::is_pointer<InputIterator1>::value && nek::is_pointer<InputIterator2>::value
            && nek::is_same<InputIterator1, InputIterator2>::value>;
        return equal_detail::equal_(first1, last1, first2, is_byte_comparable_type{});
    }
}

#endif