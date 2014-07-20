#ifndef NEK_UNINITIALIZED_DEFAULT_HPP
#define NEK_UNINITIALIZED_DEFAULT_HPP

#include <algorithm> // TODO : fill_n
#include <type_traits> // TODO : is_trivial
#include <nek/allocator/allocator.hpp>
#include <nek/allocator/allocator_traits.hpp>
#include <nek/detail/construct.hpp>
#include <nek/detail/destroy.hpp>
#include <nek/iterator/iterator_traits.hpp>
#include <nek/utility/addressof.hpp>

namespace nek
{
  namespace uninitialized_default_detail
  {
    template <class ForwardIterator, class Size>
    void uninitialized_default_n_(ForwardIterator first, Size count, std::false_type)
    {
      auto current = first;
      try {
        for (; 0 < count; --count, ++current) {
          nek::detail::construct(nek::addressof(*current));
        }
      } catch (...) {
        nek::detail::destroy(first, current);
        throw;
      }
    }

    template <class ForwardIterator, class Size>
    void uninitialized_default_n_(ForwardIterator first, Size count, std::true_type)
    {
      using value_type = typename nek::iterator_traits<ForwardIterator>::value_type;
      std::fill_n(first, count, value_type{});
    }
  }

  template <class ForwardIterator, class Size>
  void uninitialized_default_n(ForwardIterator first, Size count)
  {
    using value_type = typename nek::iterator_traits<ForwardIterator>::value_type;
    uninitialized_default_detail::uninitialized_default_n_(first, count, std::is_trivial<value_type>{});
  }

  template <class ForwardIterator, class Size, class Allocator>
  void uninitialized_default_n(ForwardIterator first, Size count, Allocator& alloctor)
  {
    using traits = nek::allocator_traits<Allocator>;
    auto current = first;
    try {
      for (; 0 < count; --count, ++first) {
        traits::construct(allocator, nek::addressof(*first_));
      }
    } catch (...) {
      for (; current != first; ++current) {
        traits::destroy(allocator, nek::addressof(*current));
      }
      throw;
    }
  }

  template <class ForwardIterator, class Size, class T>
  void uninitialized_default_n(ForwardIterator first, Size count, nek::allocator<T>&)
  {
    uninitialized_default_n(first, count);
  }
}

#endif
