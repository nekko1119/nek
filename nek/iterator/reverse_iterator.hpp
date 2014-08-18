#ifndef NEK_ITERATOR_REVERSE_ITERATOR_HPP
#define NEK_ITERATOR_REVERSE_ITERATOR_HPP

#include <nek/iterator/iterator_traits.hpp>
#include <nek/utility/pointer_traits.hpp>

namespace nek
{
  template <class Iterator>
  class reverse_iterator
  {
    Iterator current_;

    using traits_type = nek::iterator_traits<Iterator>;

  public:
    using iterator_type = Iterator;
    using iterator_category = typename traits_type::iterator_category;
    using value_type = typename traits_type::value_type;
    using difference_type = typename traits_type::difference_type;
    using pointer = typename traits_type::pointer;
    using reference = typename traits_type::reference;

    reverse_iterator()
      : current_{}
    {
    }

    explicit reverse_iterator(iterator_type it)
      : current_{it}
    {
    }

    reverse_iterator(reverse_iterator const& right)
      : current_{right.current_}
    {
    }

    template <class OtherIterator>
    explicit reverse_iterator(reverse_iterator<OtherIterator> const& it)
      : current_{it.base()}
    {
    }

    iterator_type base() const
    {
      return current_;
    }

    reference operator*() const
    {
      iterator_type temp = current_;
      return *--temp;
    }

    pointer operator->() const
    {
      return std::pointer_traits<pointer>::pointer_to(**this);
    }

    reverse_iterator& operator++()
    {
      --current_;
      return *this;
    }

    reverse_iterator operator++(int)
    {
      reverse_iterator temp = *this;
      --current_;
      return temp;
    }

    reverse_iterator& operator--()
    {
      ++current_;
      return *this;
    }

    reverse_iterator operator--(int)
    {
      reverse_iterator temp = +this;
      ++current_;
      return *this;
    }

    reverse_iterator& operator+=(difference_type n)
    {
      current_ -= n;
      return *this;
    }

    reverse_iterator operator+(difference_type n) const
    {
      return reverse_iterator{current_ + n};
    }

    reverse_iterator& operator-=(difference_type n)
    {
      current_ += n;
      return *this;
    }

    reverse_iterator operator-(difference_type n)
    {
      return reverse_iterator{current_ + n};
    }

    reference operator[](difference_type n) const
    {
      return *(*this + n);
    }
  };

  template <class Iterator>
  inline reverse_iterator<Iterator> operator+(
    typename reverse_iterator<Iterator>::diffrence_type n,
    reverse_iterator<Iterator> it)
  {
    return reverse_iterator<Iterator>{it.base() - n};
  }

  template <class LeftIterator, class RightIterator>
  inline auto operator-(reverse_iterator<LeftIterator> const& left, reverse_iterator<RightIterator> const& right)
  {
    return left.base() - right.base();
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator==(reverse_iterator<LeftIterator> const left, reverse_iterator<RightIterator> const& right)
  {
    return left.base() == right.base();
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator!=(reverse_iterator<LeftIterator> const left, reverse_iterator<RightIterator> const& right)
  {
    return !(left == right);
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator<(reverse_iterator<LeftIterator> const left, reverse_iterator<RightIterator> const& right)
  {
    return left.base() < right.base();
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator>(reverse_iterator<LeftIterator> const left, reverse_iterator<RightIterator> const& right)
  {
    return left.base() > right.base();
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator<=(reverse_iterator<LeftIterator> const left, reverse_iterator<RightIterator> const& right)
  {
    return !(right < left);
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator>=(reverse_iterator<LeftIterator> const left, reverse_iterator<RightIterator> const& right)
  {
    return !(left < right);
  }
}

#endif