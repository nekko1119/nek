#ifndef NEK_ALLOCATOR_ALLOCATOR_TRAITS_HPP
#define NEK_ALLOCATOR_ALLOCATOR_TRAITS_HPP

#include <nek/type_traits/has_difference_type.hpp>
#include <nek/type_traits/has_pointer.hpp>
#include <nek/type_traits/make_unsigned.hpp>
#include <nek/utility/has_xxx_def.hpp>
#include <nek/utility/pointer_traits.hpp>

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
  };
}

#endif