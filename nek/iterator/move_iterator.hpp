#ifndef NEK_ITERATOR_MOVE_ITERATOR_HPP
#define NEK_ITERATOR_MOVE_ITERATOR_HPP

#include <type_traits> // TODO : is_nothrow_move_constructible, is_copy_constructible
#include <nek/iterator/iterator_traits.hpp>
#include <nek/mpl/and.hpp>
#include <nek/mpl/if.hpp>
#include <nek/mpl/not.hpp>
#include <nek/utility/move.hpp>

namespace nek
{
  template <class Iterator>
  class move_iterator
  {
    Iterator current_;

  public:
    using iterator_type = Iterator;
    using iterator_category = typename iterator_traits<Iterator>::iterator_category;
    using value_type = typename iterator_traits<Iterator>::value_type;
    using difference_type = typename iterator_traits<Iterator>::difference_type;
    using pointer = Iterator;
    using reference = value_type&&;

    move_iterator() = default;

    explicit move_iterator(iterator_type it)
      : current_{it}
    {
    }

   template <class OtherIterator>
   move_iterator(move_iterator<OtherIterator> const& right)
     : current_{right.base()}
   {
   }

    iterator_type base() const
    {
      return current_;
    }

    reference operator*() const
    {
      return nek::move(*current_);
    }

    pointer operator->() const
    {
      return current_; 
    }

    move_iterator& operator++()
    {
      ++current_;
      return *this;
    }

    move_iterator operator++(int)
    {
      move_iterator temp = *this;
      ++current_;
      return temp;
    }

    move_iterator& operator--()
    {
      --current_;
      return *this;
    }

    move_iterator operator--(int)
    {
      move_iterator temp = *this;
      --current_;
      return temp;
    }

    move_iterator& operator+=(difference_type n)
    {
      current_ += n;
      return *this;
    }

    move_iterator operator+(difference_type n) const  
    {
      return move_iterator{current_ + n};
    }

    move_iterator& operator-=(difference_type n)
    {
      current_ -= n;
      return *this;
    }

    move_iterator operator-(difference_type n) const
    {
      return move_iterator{current_ - n};
    }

    reference operator[](difference_type n) const
    {
      return nek::move(current_[n]);
    }
  };

  template <class Iterator>
  inline move_iterator<Iterator> operator+(typename iterator_traits<Iterator>::difference_type n, move_iterator<Iterator> const& it)
  {
    return it + n;
  }

  template <class LeftIterator, class RightIterator>
  inline auto operator-(move_iterator<LeftIterator> const& left, move_iterator<RightIterator> const& right)
  {
    return left.base() - right.base();
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator==(move_iterator<LeftIterator> const& left, move_iterator<RightIterator> const& right)
  {
    return left.base() == right.base();
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator!=(move_iterator<LeftIterator> const& left, move_iterator<RightIterator> const& right)
  {
    return !(left.base() == right.base());
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator<(move_iterator<LeftIterator> const& left, move_iterator<RightIterator> const& right)
  {
    return left.base() < right.base();
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator>(move_iterator<LeftIterator> const& left, move_iterator<RightIterator> const& right)
  {
    return right.base() < left.base();
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator<=(move_iterator<LeftIterator> const& left, move_iterator<RightIterator> const& right)
  {
    return !(right.base() < left.base());
  }

  template <class LeftIterator, class RightIterator>
  inline bool operator>=(move_iterator<LeftIterator> const& left, move_iterator<RightIterator> const& right)
  {
    return !(left.base() < right.base());
  }

  template <class Iterator>
  inline move_iterator<Iterator> make_move_iterator(Iterator it)
  {
    return move_iterator<Iterator>{it};
  }

  namespace move_iterator_detail
  {
    template <class Iterator,
    class ValueType =
      typename iterator_traits<Iterator>::value_type,
    class Return =
      mpl::if_t<
      mpl::and_<mpl::not_<std::is_nothrow_move_constructible<ValueType>>,
      std::is_copy_constructible<ValueType>>,
      Iterator, move_iterator<Iterator>>
      >
      Return make_move_if_noexcept_iterator_(Iterator it)
    {
      return Return{it};
    }
  }

  template <class Iterator>
  inline auto make_if_noexcept_iterator(Iterator it)
  {
    return move_iterator_detail::make_move_if_noexcept_iterator_(it);
  }
}

#endif