#ifndef NEK_TYPE_TRAITS_HAS_ITERATOR_HPP
#define NEK_TYPE_TRAITS_HAS_ITERATOR_HPP

#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/void_t.hpp>

namespace nek
{
    template <class, class = void>
    struct has_iterator
        : public false_type
    {
    };

    template <class T>
    struct has_iterator<T, void_t<typename T::iterator>>
        : public true_type
    {
    };
}

#endif