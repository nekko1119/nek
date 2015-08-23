#ifndef NEK_ALLOCATOR_ALLOCATOR_HPP
#define NEK_ALLOCATOR_ALLOCATOR_HPP

#include <cstddef>
#include <exception>
#include <new>
#include <nek/type_traits/integral_constant.hpp>
#include <nek/utility/addressof.hpp>
#include <nek/utility/forward.hpp>

namespace nek
{
    template <class T>
    class allocator
    {
    public:
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using const_pointer = T const*;
        using reference = T&;
        using const_reference = T const&;
        using value_type = T;
        using propagate_on_container_copy_assignment = false_type;
        using propagate_on_container_move_assignment = false_type;
        using propagate_on_container_swap = false_type;

        template <class U>
        struct rebind
        {
            using other = allocator<U>;
        };

        allocator() = default;

        template <class U>
        allocator(allocator<U> const&)
        {
        }


        allocator select_on_container_copy_construction() const
        {
            return *this;
        }

        pointer allocate(size_type count, void const* = nullptr) const
        {
            if (max_size() < count) {
                throw std::bad_alloc();
            }
            return static_cast<pointer>(::operator new(count * sizeof(value_type)));
        }

        void deallocate(pointer ptr, size_type) const
        {
            ::operator delete(ptr);
        }

        template <class U, class... Args>
        void construct(U* other, Args&&... args) const
        {
            ::new (static_cast<void*>(other)) U(forward<Args>(args)...);
        }

        template <class U>
        void destroy(U* other) const
        {
            other->~U();
        }

        inline pointer address(reference value)
        {
            return addressof(value);
        }

        inline const_pointer address(const_reference value) const
        {
            return addressof(value);
        }

        inline size_type max_size() const
        {
            return static_cast<size_type>(-1) / sizeof(value_type);
        }
    };

    template <>
    class allocator<void>
    {
    public:
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using value_type = void;
        using pointer = void*;
        using const_pointer = void const*;;
        using void_pointer = void*;
        using const_void_pointer = void const*;

        template <class U>
        struct rebind
        {
            typedef allocator<U> other;
        };

        allocator() = default;
        allocator(allocator const&) = default;

        template <class U>
        allocator(allocator<U> const&)
        {
        }

        template <class U>
        allocator<void>& operator=(allocator<U> const&)
        {
            return *this;
        }
    };

    template <class T, class U>
    inline bool operator==(allocator<T> const&, allocator<U> const&)
    {
        return true;
    }

    template <class T, class U>
    inline bool operator!=(allocator<T> const& left, allocator<U> const& right)
    {
        return !(left == right);
    }
}

#endif
