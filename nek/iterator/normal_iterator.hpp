#ifndef NEK_ITERATOR_NORMAL_ITERATOR_HPP
#define NEK_ITERATOR_NORMAL_ITERATOR_HPP

#include <nek/iterator/iterator_traits.hpp>
#include <nek/type_traits/enable_if.hpp>
#include <nek/type_traits/is_same.hpp>

namespace nek
{
  template <class Iterator, class Container>
  class normal_iterator
  {
    Iterator current_;

  public:
    using iterator_type = Iterator;
    using iterator_category = typename iterator_traits<Iterator>::iterator_category;
    using value_type = typename iterator_traits<Iterator>::value_type;
    using difference_type = typename iterator_traits<Iterator>::difference_type;
    using pointer = typename iterator_traits<Iterator>::pointer;
    using reference = typename iterator_traits<Iterator>::reference;

    normal_iterator() = default;

    normal_iterator(normal_iterator const&) = default;

    template <class OtherIterator>
    normal_iterator(normal_iterator<OtherIterator, 
      typename enable_if_t<
        typename is_same<OtherIterator, typename Container::pointer>::type,
      Container>> const& it)
      : current_{it.base()}
    {
    }

    iterator_type const& base() const
    {
      return current_;
    }

    reference operator*() const
    {
      return *current_;
    }

    pointer operator->() const
    {
      return current_;
    }

    normal_iterator& operator++()
    {
      ++current_;
      return *this;
    }

    normal_iterator operator++(int)
    {
      return normal_iterator{current_++};
    }

    normal_iterator& operator--()
    {
      --current_;
      return *this;
    }

    normal_iterator operator--(int)
    {
      return normal_iterator{current_--};
    }

    normal_iterator& operator+=(difference_type const& n)
    {
      current_ += n;
      return *this;
    }

    normal_iterator operator+(difference_type const& n) const
    {
      return normal_iterator{current_ + n};
    }

    normal_iterator& operator-=(difference_type const& n)
    {
      current_ -= n;
      return *this;
    }

    normal_iterator operator-(difference_type const& n) const
    {
      return normal_iterator{current_ - n};
    }

    reference operator[](difference_type const& n) const
    {
      return current_[n];
    }
  };

  //template <class LeftIterator, class RightIterator, class Container>
  //inline bool operator==(normal_iterator
}

#endif