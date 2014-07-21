#ifndef NEK_ITERATOR_ITERATOR_TRAITS_HPP
#define NEK_ITERATOR_ITERATOR_TRAITS_HPP

#include <cstddef>
#include <iterator>
#include <nek/iterator/tag.hpp>
#include <nek/type_traits/integral_constant.hpp>

namespace nek
{
  namespace iterator_traits_detail
  {
    template <class Tag>
    struct to_nek_iterator_category
    {
      using type = Tag;
    };

    template <>
    struct to_nek_iterator_category<std::input_iterator_tag>
    {
      using type = nek::input_iterator_tag;
    };

    template <>
    struct to_nek_iterator_category<std::output_iterator_tag>
    {
      using type = nek::output_iterator_tag;
    };

    template <>
    struct to_nek_iterator_category<std::forward_iterator_tag>
    {
      using type = nek::forward_iterator_tag;
    };

    template <>
    struct to_nek_iterator_category<std::bidirectional_iterator_tag>
    {
      using type = nek::bidirectional_iterator_tag;
    };

    template <>
    struct to_nek_iterator_category<std::random_access_iterator_tag>
    {
      using type = nek::random_access_iterator_tag;
    };
  }

  template <class Iterator>
  struct iterator_traits
  {
    using iterator_category =
      typename iterator_traits_detail::to_nek_iterator_category<typename Iterator::iterator_category>::type;
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