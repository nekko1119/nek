#ifndef NEK_ITERATOR_NORMAL_ITERATOR_HPP
#define NEK_ITERATOR_NORMAL_ITERATOR_HPP

#include <nek/iterator/iterator_traits.hpp>

namespace nek
{
  template <class Iterator>
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

    explicit normal_iterator(iterator_type const& it)
      : current_{it}
    {
    }

    template <class OtherIterator>
    normal_iterator(normal_iterator<OtherIterator> const& right)
      : current_{right.base()}
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
      return &*current_;
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

  template <class Iterator>
  inline normal_iterator<Iterator> operator+(
    typename normal_iterator<Iterator>::difference_type n,
    normal_iterator<Iterator> const& it)
  {
    return normal_iterator<Iterator>{it.base() + n};
  }

  template <class LeftIterator, class RightIterator>
  inline auto operator-(normal_iterator<LeftIterator> const& left, normal_iterator<RightIterator> const& right)
  {
    return left.base() - right.base();
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator==(normal_iterator<LeftIterator> const& left, normal_iterator<RightIterator> const& right)
  {
    return left.base() == right.base();
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator!=(normal_iterator<LeftIterator> const& left, normal_iterator<RightIterator> const& right)
  {
    return !(left == right);
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator<(normal_iterator<LeftIterator> const& left, normal_iterator<RightIterator> const& right)
  {
    return left.base() < right.base();
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator>(normal_iterator<LeftIterator> const& left, normal_iterator<RightIterator> const& right)
  {
    return right.base() < left.base();
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator<=(normal_iterator<LeftIterator> const& left, normal_iterator<RightIterator> const& right)
  {
    return !(right.base() < left.base());
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator>=(normal_iterator<LeftIterator> const& left, normal_iterator<RightIterator> const& right)
  {
    return !(left.base() < right.base());
  }

}

#endif