#ifndef NEK_CONTAINER_DETAIL_DESTROY_HPP
#define NEK_CONTAINER_DETAIL_DESTROY_HPP

#include <type_traits> // TODO : is_trivially_destructible
#include <nek/allocator/allocator_traits.hpp>
#include <nek/iterator/iterator_traits.hpp>
#include <nek/utility/addressof.hpp>

namespace nek
{
  namespace container_detail
  {
    template <class ForwardIterator, class Allocator>
    void destroy(ForwardIterator first, ForwardIterator last, Allocator& allocater, std::true_type)
    {
    }

    template <class ForwardIterator, class Allocator>
    void destroy(ForwardIterator first, ForwardIterator last, Allocator& allocater, std::false_type)
    {
      using traits = nek::allocator_traits<Allocator>;
      for (; first != last; ++first) {
        traits::destroy(allocator, nek::addressof(*first));
      }
    }

    template <class ForwardIterator, class Allocator>
    void destroy(ForwardIterator first, ForwardIterator last, Allocator& allocator)
    {
      using value_type = typename nek::iterator_traits<ForwardIterator>::value_type;
      destroy(first, last, allocator, std::is_trivially_destructible<value_type>{});
    }
  }
}

#endif