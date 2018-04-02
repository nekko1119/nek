#ifndef NEK_ITERATOR_ITERATOR_HPP
#define NEK_ITERATOR_ITERATOR_HPP

#include <cstddef>

namespace nek
{
    template <class Category, class T, class Difference = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator
    {
        using iterator_category = Category;
        using value_type = T;
        using difference_type = Difference;
        using pointer = Pointer;
        using reference = Reference;
    protected:
        ~iterator() = default;
    };
}

#endif
