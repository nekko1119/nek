#ifndef NEK_ITERATOR_ITERATOR_TRAITS_HPP
#define NEK_ITERATOR_ITERATOR_TRAITS_HPP

#include <cstddef>
#include <nek/iterator/tag.hpp>

namespace nek
{
  template <class Iterator>
  struct iterator_traits
  {
    using iterator_category = typename Iterator::iterator_category;
    using value_type = typename Iterator::value_type;
    using difference_type = typename Iterator::difference_type;
    using pointer = typename Iterator::pointer;
    using reference = typename Iterator::reference;
  };

  template <class T>
  struct iterator_traits<T*>
  {
    using iterator_category = nek::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;
  };

  template <class T>
  struct iterator_traits<T const*>
  {
    using iterator_category = nek::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T const*;
    using reference = T const&;
  };
}

#endif