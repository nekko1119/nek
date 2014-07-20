#ifndef NEK_UNINITIALIZED_COPY_HPP
#define NEK_UNINITIALIZED_COPY_HPP

#include <algorithm> // TODO : copy
#include <type_traits> // TODO : is_trivial
#include <nek/detail/construct.hpp>
#include <nek/detail/destroy.hpp>
#include <nek/iterator/iterator_traits.hpp>
#include <nek/utility/addressof.hpp>

namespace nek
{
  // uninitialized_copy
  namespace uninitialized_copy_detail
  {
    template <class InputIterator, class ForwardIterator>
    void uninitialized_copy_(InputIterator first, InputIterator last, ForwardIterator dest, std::false_type)
    {
      auto current = dest;
      try {
        for (; first != last; ++first, ++current) {
          detail::construct(addressof(*current), *first);
        }
      } catch (...) {
        detail::destroy(dest, current);
        throw;
      }
    }

    template <class InputIterator, class ForwardIterator>
    void uninitialized_copy_(InputIterator first, InputIterator last, ForwardIterator dest, std::true_type)
    {
      std::copy(first, last, dest);
    }
  }

  template <class InputIterator, class ForwardIterator>
  void uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator dest)
  {
    using in_value_type = typename iterator_traits<InputIterator>::value_type;
    using out_value_type = typename iterator_traits<ForwardIterator>::value_type;
    uninitialized_copy_detail::uninitialized_copy_(first, last, dest,
      std::integral_constant<bool, std::is_trivial<in_value_type>::value && std::is_trivial<out_value_type>::value>{});
  }

  // uninitialized_copy_n
  namespace uninitialized_copy_detail
  {
    template <class InputIterator, class Size, class ForwardIterator>
    void uninitilized_copy_n_(InputIterator first, Size count, ForwardIterator dest, input_iterator_tag)
    {
      auto current = dest;
      try {
        for (; 0 < count; --count, ++current, ++first) {
          detail::construct(addressof(*current), *first);
        }
        return current;
      } catch (...) {
        detail::destroy(dest, current);
        throw;
      }
    }

    template <class RandomAccessIterator, class Size, class ForwardIterator>
    void uninitilized_copy_n_(RandomAccessIterator first, Size count, ForwardIterator dest, random_access_iterator_tag)
    {
      uninitialized_copy(first, first + count, dest);
    }
  }

  template <class InputIterator, class Size, class ForwardIterator>
  void uninitialized_copy_n(InputIterator first, Size count, ForwardIterator dest)
  {
    using tag = typename iterator_traits<InputIterator>::iterator_category;
    uninitialized_copy_detail::uninitilized_copy_n_(first, count, dest, tag{});
  }
}

#endif