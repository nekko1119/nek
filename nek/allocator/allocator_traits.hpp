#ifndef NEK_ALLOCATOR_ALLOCATOR_TRAITS_HPP
#define NEK_ALLOCATOR_ALLOCATOR_TRAITS_HPP

#include <new>
#include <limits>

#include <nek/type_traits/has_difference_type.hpp>
#include <nek/type_traits/has_pointer.hpp>
#include <nek/type_traits/make_unsigned.hpp>
#include <nek/utility/forward.hpp>
#include <nek/utility/has_xxx_def.hpp>
#include <nek/utility/pointer_traits.hpp>
#include <nek/utility/swap.hpp>

namespace nek
{
  namespace allocator_traits_detail
  {
    NEK_HAS_XXX_TYPE_DEF(const_pointer);
    NEK_HAS_XXX_TYPE_DEF(void_pointer);
    NEK_HAS_XXX_TYPE_DEF(const_void_pointer);
    NEK_HAS_XXX_TYPE_DEF(size_type);
    NEK_HAS_XXX_TYPE_DEF(propagate_on_container_copy_assignment);
    NEK_HAS_XXX_TYPE_DEF(propagate_on_container_move_assignment);
    NEK_HAS_XXX_TYPE_DEF(propagate_on_container_swap);
    namespace detail
    {
      template <class Allocator, class T, class = Allocator::template rebind<T>::type>
      nek::true_type has_rebind(int);

      template <class, class>
      nek::false_type has_rebind(long);
    }

    template <class Allocator, class T>
    struct has_rebind
      : public decltype(detail::has_rebind<Allocator, T>(0))
    {
    };

    template <class T, bool = nek::has_pointer<T>::value>
    struct pointer
    {
      using type = typename T::pointer;
    };

    template <class T>
    struct pointer<T, false>
    {
      using type = typename T::value_type*;
    };

    template <class T, bool = has_const_pointer<T>::value>
    struct const_pointer
    {
      using type = typename T::const_pointer;
    };

    template <class T>
    struct const_pointer<T, false>
    {
    private:
      using pointer = typename pointer<T>::type;
      using value_type = typename T::value_type;

    public:
      using type = typename pointer_traits<pointer>::template rebind<const value_type>::other;
    };

    template <class T, bool = has_void_pointer<T>::value>
    struct void_pointer
    {
      using type = typename T::void_pointer;
    };

    template <class T>
    struct void_pointer<T, false>
    {
    private:
      using pointer = typename pointer<T>::type;

    public:
      using type = typename pointer_traits<pointer>::template rebind<void>::other;
    };

    template <class T, bool = has_const_void_pointer<T>::value>
    struct const_void_pointer
    {
      using type = typename T::const_void_pointer;
    };

    template <class T>
    struct const_void_pointer<T, false>
    {
    private:
      using pointer = typename pointer<T>::type;

    public:
      using type = typename pointer_traits<pointer>::template rebind<const void>::other;
    };

    template <class T, bool = nek::has_difference_type<T>::value>
    struct difference_type
    {
      using type = typename T::difference_type;
    };

    template <class T>
    struct difference_type<T, false>
    {
    private:
      using pointer = typename pointer<T>::type;

    public:
      using type = typename pointer_traits<pointer>::difference_type;
    };

    template <class T, bool = has_size_type<T>::value>
    struct size_type
    {
      using type = typename T::size_type;
    };

    template <class T>
    struct size_type<T, false>
    {
    private:
      using difference_type = typename difference_type<T>::type;

    public:
      using type = typename make_unsigned<difference_type>::type;
    };

    template <class T, bool = has_propagate_on_container_copy_assignment<T>::value>
    struct propagate_on_container_copy_assignment
    {
      using type = typename T::propagate_on_container_copy_assignment;
    };

    template <class T>
    struct propagate_on_container_copy_assignment<T, false>
    {
      using type = false_type;
    };

    template <class T, bool = has_propagate_on_container_move_assignment<T>::value>
    struct propagate_on_container_move_assignment
    {
      using type = typename T::propagate_on_container_move_assignment;
    };

    template <class T>
    struct propagate_on_container_move_assignment<T, false>
    {
      using type = false_type;
    };

    template <class T, bool = has_propagate_on_container_swap<T>::value>
    struct propagate_on_container_swap
    {
      using type = typename T::propagate_on_container_swap;
    };

    template <class T>
    struct propagate_on_container_swap<T, false>
    {
      using type = false_type;
    };

    template <class Allocator, class T, bool = has_rebind<Allocator, T>::value>
    struct rebind_alloc
    {
      using type = typename Allocator::template rebind<T>::other;
    };

    template <template <class, class...> class Allocator, class T, class U, class... Args>
    struct rebind_alloc<Allocator<U, Args...>, T, false>
    {
      using type = Allocator<T, Args...>;
    };

    struct dispatcher
    {
      template <class Allocator, class Size, class ConstVoidPointer>
      static auto allocate(int, Allocator& allocator, Size count, ConstVoidPointer hint)
        -> decltype(allocator.allocate(count, hint))
      {
        return allocator.allocate(count, hint);
      }

      template <class Allocator, class Size, class ConstVoidPointer>
      static auto allocate(long, Allocator& allocator, Size count, ConstVoidPointer)
        -> decltype(allocator.allocate(count))
      {
        return allocator.allocate(count);
      }

      template <class Allocator, class T, class... Args>
      static auto construct(int, Allocator& allocator, T* p, Args&&... args)
        -> decltype(allocator.construct(p, nek::forward<Args>(args)...))
      {
        allocator.construct(p, nek::forward<Args>(args)...);
      }

      template <class Allocator, class T, class... Args>
      static auto construct(long, Allocator& allocator, T* p, Args&&... args)
        -> void
      {
        ::new (static_cast<void*>(p)) T(nek::forward<Args>(args)...);
      }

      template <class Allocator, class T>
      static auto destroy(int, Allocator& allocator, T* p)
        -> decltype(allocator.destroy(p))
      {
        allocator.destroy(p);
      }

      template <class Allocator, class T>
      static auto destroy(long, Allocator& allocator, T* p)
        -> void
      {
        p->~T();
      }

      template <class Allocator>
      static auto max_size(int, Allocator& allocator)
        -> decltype(allocator.max_size())
      {
        return allocator.max_size();
      }

      template <class Allocator>
      static auto max_size(long, Allocator& allocator)
        -> typename size_type<Allocator>::type
      {
        return std::numeric_limits<typename size_type<Allocator>::type>::max();
      }

      template <class Allocator>
      static auto select_on_container_copy_construction(int, Allocator const& allocator)
        -> decltype(allocator.select_on_container_copy_construction())
      {
        return allocator.select_on_container_copy_construction();
      }

      template <class Allocator>
      static auto select_on_container_copy_construction(long, Allocator const& allocator)
        -> Allocator
      {
        return allocator;
      }
    };
    template <class Allocator>
    inline void swap_(Allocator& left, Allocator& right, nek::true_type)
    {
      using nek::swap;
      swap(left, right);
    }

    template <class Allocator>
    inline void swap_(Allocator&, Allocator&, nek::false_type)
    {
      // do nothing
    }
  }

  template <class Allocator>
  struct allocator_traits
  {
    using allocator_type = Allocator;
    using value_type = typename Allocator::value_type;
    using pointer = typename allocator_traits_detail::pointer<Allocator>::type;
    using const_pointer = typename allocator_traits_detail::const_pointer<Allocator>::type;
    using void_pointer = typename allocator_traits_detail::void_pointer<Allocator>::type;
    using const_void_pointer = typename allocator_traits_detail::const_void_pointer<Allocator>::type;
    using difference_type = typename allocator_traits_detail::difference_type<Allocator>::type;
    using size_type = typename allocator_traits_detail::size_type<Allocator>::type;
    using propagate_on_container_copy_assignment = typename allocator_traits_detail::propagate_on_container_copy_assignment<Allocator>::type;
    using propagate_on_container_move_assignment = typename allocator_traits_detail::propagate_on_container_move_assignment<Allocator>::type;
    using propagate_on_container_swap = typename allocator_traits_detail::propagate_on_container_swap<Allocator>::type;
    template <class T>
    using rebind_alloc = typename allocator_traits_detail::rebind_alloc<Allocator, T>::type;
    template <class T>
    using rebind_traits = allocator_traits<rebind_alloc<T>>;

    static pointer allocate(Allocator& allocator, size_type count)
    {
      return allocator.allocate(count);
    }

    static pointer allocate(Allocator& allocator, size_type count, const_void_pointer hint)
    {
      return allocator_traits_detail::dispatcher::allocate(0, allocator, count, hint);
    }

    static void deallocate(Allocator& allocator, pointer p, size_type count)
    {
      allocator.deallocate(p, count);
    }

    template <class T, class... Args>
    static void construct(Allocator& allocator, T* p, Args... args)
    {
      allocator_traits_detail::dispatcher::construct(0, allocator, p, nek::forward<Args>(args)...);
    }

    template <class T>
    static void destroy(Allocator& allocator, T* p)
    {
      allocator_traits_detail::dispatcher::destroy(0, allocator, p);
    }

    static size_type max_size(Allocator& allocator)
    {
      return allocator_traits_detail::dispatcher::max_size(0, allocator);
    }

    static Allocator select_on_container_copy_construction(Allocator const& allocator)
    {
      return allocator_traits_detail::dispatcher::select_on_container_copy_construction(0, allocator);
    }

    inline static void swap(Allocator& left, Allocator& right)
    {
      allocator_traits_detail::swap_(left, right, propagate_on_container_swap{});
    }
  };
}

#endif