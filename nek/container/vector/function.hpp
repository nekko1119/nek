#ifndef NEK_CONTAINER_VECTOR_FUNCTION_HPP
#define NEK_CONTAINER_VECTOR_FUNCTION_HPP

#include <nek/container/function.hpp>
#include <nek/mpl/not.hpp>
#include <nek/type_traits/enable_if.hpp>
#include <nek/type_traits/is_integral.hpp>
#include <nek/container/vector/vector.hpp>

namespace nek
{
    template <class T, class Allocator, class InputIterator>
    inline enable_if_t<nek::mpl::not_<nek::is_integral<InputIterator>>> assign(vector<T, Allocator>& v, InputIterator first, InputIterator last)
    {
        nek::clear(v);
        nek::insert(v, first, last);
    }

    template <class T, class Allocator>
    inline void assign(vector<T, Allocator>& v, std::initializer_list<T> list)
    {
        v = list;
    }

    template <class T, class Allocator>
    inline void assign(vector<T, Allocator>& v, typename vector<T, Allocator>::size_type count, T const& value)
    {
        nek::clear(v);
        v.insert(v.begin(), count, value);
    }

    template <class T, class Allocator>
    void shrink_to_fit(vector<T, Allocator>& v)
    {
        if (nek::size(v) == v.capacity()) {
            return;
        }

        nek::vector<T, Allocator>(
            nek::make_move_if_noexcept_iterator(v.begin()),
            nek::make_move_if_noexcept_iterator(v.end()),
            v.get_allocator()).swap(v);
    }

    template <class T, class Allocator>
    void resize(vector<T, Allocator>& v, typename vector<T, Allocator>::size_type new_size, T const& value)
    {
        if (new_size < nek::size(v)) {
            v.erase(v.begin() + new_size, v.end());
        } else if (nek::size(v) < new_size) {
            v.insert(v.end(), new_size - nek::size(v), value);
        }
    }

    template <class T, class Allocator>
    void resize(vector<T, Allocator>& v, typename vector<T, Allocator>::size_type new_size)
    {
        nek::resize(v, new_size, T());
    }
}

#endif
