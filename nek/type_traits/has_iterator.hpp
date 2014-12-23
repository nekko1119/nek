#ifndef NEK_TYPE_TRAITS_HAS_ITERATOR_HPP
#define NEK_TYPE_TRAITS_HAS_ITERATOR_HPP

#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
    namespace has_iterator_detail
    {
        template <class T, class = typename T::iterator>
        nek::true_type has_iterator(T*);

        template <class>
        nek::false_type has_iterator(...);
    }

    template <class T>
    struct has_iterator
        : public decltype(has_iterator_detail::has_iterator<T>(nullptr))
    {
    };
}

#endif