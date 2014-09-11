#ifndef NEK_UNINITIAKUZED_UNINITIALIZED_FILL_HPP
#define NEK_UNINITIALIZED_UNINITIALIZED_FILL_HPP

#include <nek/algorithm/fill.hpp>
#include <nek/algorithm/fill_n.hpp>
#include <nek/allocator/allocator.hpp>
#include <nek/allocator/allocator_traits.hpp>
#include <nek/detail/construct.hpp>
#include <nek/detail/destroy.hpp>
#include <nek/type_traits/is_trivial.hpp>
#include <nek/utility/addressof.hpp>

namespace nek
{
  namespace uninitialized_fill_detail
  {
    template <class ForwardIterator, class T>
    inline void uninitialized_fill_(ForwardIterator first, ForwardIterator last, T const& value, nek::true_type)
    {
      nek::fill(first, last, value);
    }

    template <class ForwardIterator, class T>
    inline void uninitialized_fill_(ForwardIterator first, ForwardIterator last, T const& value, nek::false_type)
    {
      auto current = first;
      try {
        for (; current != last; ++current) {
          nek::detail::construct(nek::addressof(*current), value);
        }
      } catch (...) {
        nek::detail::destroy(first, current);
        throw;
      }
    }
  }

  template <class ForwardIterator, class T>
  inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, T const& value)
  {
    uninitialized_fill_detail::uninitialized_fill_(first, last, value, nek::is_trivial<T>{});
  }

  template <class ForwardIterator, class T, class Allocator>
  inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, T const& value, Allocator& allocator)
  {
    using traits = nek::allocator_traits<Allocator>;
    auto current = first;
    try {
      for (; current != last; ++current) {
        traits::construct(allocator, nek::addressof(*current), value);
      }
    } catch (...) {
      traits::destroy(allocator, first, current);
      throw;
    }
  }

  template <class ForwardIterator, class T>
  inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, T const& value, nek::allocator<T>& allocator)
  {
    uninitialized_fill(first, last, value);
  }

  namespace uninitialized_fill_n_detail
  {
    template <class ForwardIterator, class Size, class T>
    inline ForwardIterator uninitialized_fill_n_(ForwardIterator first, Size count, T const& value, nek::true_type)
    {
      return nek::fill_n(first, count, value);
    }

    template <class ForwardIterator, class Size, class T>
    inline ForwardIterator uninitialized_fill_n_(ForwardIterator first, Size count, T const& value, nek::false_type)
    {
      auto current = first;
      try {
        for (; 0 < count; --count, ++current) {
          nek::detail::construct(nek::addressof(*current), value);
        }
        return current;
      } catch (...) {
        nek::detail::destroy(first, current);
        throw;
      }
    }
  }

  template <class ForwardIterator, class Size, class T>
  ForwardIterator uninitialized_fill_n(ForwardIterator first, Size count, T const& value)
  {
    return uninitialized_fill_n_detail::uninitialized_fill_n(first, count, value);
  }

  template <class ForwardIterator, class Size, class T, class Allocator>
  ForwardIterator uninitialized_fill_n(ForwardIterator first, Size count, T const& value, Allocator& allocator)
  {
    using traits = nek::allocator_traits<Allocator>;
    auto current = first;
    try {
      for (; 0 < count; --count, ++current) {
        traits::construct(allocator, nek::addressof(*current), value);
      }
      return current;
    } catch (...) {
      for (; first != current; ++first) {
        traits::destroy(allocator, nek::addressof(*first));
      }
      throw;
    }
  }
  }
}

#endif
