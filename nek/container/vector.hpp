#ifndef NEK_CONTAINER_VECTOR_HPP
#define NEK_CONTAINER_VECTOR_HPP

#include <cassert>
#include <initializer_list>
#include <stdexcept>

#include <algorithm> // TODO : std::move, std::copy_backward, std::fill
#include <memory> // TODO : std::uninitialized_fill
#include <nek/algorithm/max.hpp>
#include <nek/container/container_fwd.hpp>
#include <nek/algorithm/rotate.hpp>
#include <nek/container/function.hpp>
#include <nek/detail/destroy.hpp>
#include <nek/allocator/allocator.hpp>
#include <nek/allocator/allocator_traits.hpp>
#include <nek/iterator/distance.hpp>
#include <nek/iterator/iterator_traits.hpp>
#include <nek/iterator/move_iterator.hpp>
#include <nek/iterator/normal_iterator.hpp>
#include <nek/iterator/reverse_iterator.hpp>
#include <nek/uninitialized/uninitialized_copy.hpp>
#include <nek/uninitialized/uninitialized_default.hpp>
#include <nek/uninitialized/uninitialized_move.hpp>
#include <nek/utility/forward.hpp>
#include <nek/utility/swap.hpp>
#include <vector>

namespace nek
{
  namespace vector_detail
  {
    template <class T, class Allocator>
    class vector_base
      : private nek::allocator_traits<Allocator>::template rebind_alloc<T>
    {
    protected:
      using base_type = typename nek::allocator_traits<Allocator>::template rebind_alloc<T>;
      using alloc_type = base_type; // NOTE : workaround. base_type::base_type is not allowed.
      using pointer = typename nek::allocator_traits<alloc_type>::pointer;
      using size_type = typename nek::allocator_traits<alloc_type>::size_type;

    private:
      pointer first_; // head pointer to reserved and initialized storage
      pointer last_; // initialized storage end
      pointer capacity_end_; // reserved storage end

      void reserve(size_type count)
      {
        first_ = base_type::allocate(count);
        last_ = first_;
        capacity_end_ = first_ + count;
      }

    protected:
      pointer& first() noexcept
      {
        return first_;
      }

      pointer const& first() const noexcept
      {
        return first_;
      }

      pointer& last() noexcept
      {
        return last_;
      }

      pointer const& last() const noexcept
      {
        return last_;
      }

      pointer& capacity_end() noexcept
      {
        return capacity_end_;
      }

      pointer const& capacity_end() const noexcept
      {
        return capacity_end_;
      }

      alloc_type& allocator() noexcept
      {
        return *(static_cast<alloc_type*>(this));
      }

      alloc_type const& allocator() const noexcept
      {
        return *(static_cast<alloc_type const*>(this));
      }

    public:
      vector_base()
        : base_type{},
        first_{nullptr},
        last_{nullptr},
        capacity_end_{nullptr}
      {
      }

      explicit vector_base(Allocator const& allocator)
        : base_type{allocator},
        first_{nullptr},
        last_{nullptr},
        capacity_end_{nullptr}
      {
      }

      explicit vector_base(size_type count)
        : base_type{}
      {
        reserve(count);
      }

      vector_base(size_type count, Allocator const& allocator)
        : base_type{allocator}
      {
        reserve(count);
      }

      ~vector_base()
      {
        if (first_) {
          base_type::deallocate(first_, capacity_end_ - first_);
        }
      }
    };
  }

  template <class T, class Allocator = nek::allocator<T>>
  class vector
    : private vector_detail::vector_base<T, Allocator>
  {
    using base_type = vector_detail::vector_base<T, Allocator>;
    using alloc_traits = nek::allocator_traits<typename base_type::alloc_type>;

  public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = typename base_type::size_type;
    using difference_type = typename alloc_traits::difference_type;
    using reference = T&;
    using const_reference = T const&;
    using pointer = typename base_type::pointer;
    using const_pointer = typename alloc_traits::const_pointer;
    using iterator = normal_iterator<pointer>;
    using const_iterator = normal_iterator<const_pointer>;
    using reverse_iterator = nek::reverse_iterator<iterator>;
    using const_reverse_iterator = nek::reverse_iterator<const_iterator>;

    vector()
      : base_type{}
    {
    }

    explicit vector(Allocator const& allocator)
      : base_type{allocator}
    {
    }

    explicit vector(size_type count)
      : base_type{count}
    {
      nek::uninitialized_default_n(first(), count, allocator());
      last() = capacity_end();
    }

    template <class InputIterator>
    vector(InputIterator first, InputIterator last)
      : vector{first, last, allocator_type{}}
    {
    }

    template <class InputIterator>
    vector(InputIterator first, InputIterator last, Allocator const& allocator)
      : base_type{allocator}
    {
      range_initialize(first, last);
    }

    vector(std::initializer_list<value_type> list)
      : vector{list, allocator_type{}}
    {
      range_initialize(list.begin(), list.end(), std::random_access_iterator_tag{});
    }

    vector(std::initializer_list<value_type> list, Allocator const& allocator)
      : base_type{allocator}
    {
      range_initialize(list.begin(), list.end(), std::random_access_iterator_tag{});
    }

    vector(vector const& right)
      : vector{right, allocator_type{}}
    {
    }

    vector(vector const& right, Allocator const& allocator)
      : base_type{nek::size(right), alloc_traits::select_on_container_copy_construction(allocator)}
    {
      last() = nek::uninitialized_copy(right.begin(), right.end(), first());
    }

    vector(vector&& right)
      : vector(nek::move(right), allocator_type{})
    {
    }

    vector(vector&& right, Allocator const& allocator)
      : base_type{allocator}
    {
      move_construct(nek::move(right), alloc_traits::propagate_on_container_move_assignment{});
    }

    ~vector()
    {
      detail::destroy(first(), last(), allocator());
    }

    allocator_type get_allocator() const noexcept
    {
      return allocator_type{allocator()};
    }

    size_type capacity() const noexcept
    {
      return static_cast<size_type>(capacity_end() - first());
    }

    size_type max_size() const noexcept
    {
      return allocator().max_size();
    }

    pointer data() noexcept
    {
      return first();
    }

    const_pointer data() const noexcept
    {
      return first();
    }

    void swap(vector& right)
    {
      using nek::swap;
      swap(first(), right.first());
      swap(last(), right.last());
      swap(capacity_end(), right.capacity_end());
      alloc_traits::swap(allocator(), right.allocator());
    }

    template <class InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      nek::clear(*this);
      assign_(first, last);
    }

    void reserve(size_type count)
    {
      // validate
      if (allocator().max_size() < count) {
        throw std::length_error{"nek::vector<T>::reserve : size is too long."};
      }
      if (count < capacity()) {
        return;
      }

      // allocate new buffer
      pointer new_buffer = allocator().allocate(count);

      size_type const size = nek::size(*this);

      // copy or move new buffer
      try {
        nek::uninitialized_copy(
          nek::make_move_if_noexcept_iterator(first()),
          nek::make_move_if_noexcept_iterator(last()),
          new_buffer, allocator());
      } catch (...) {
        allocator().deallocate(new_buffer, count);
        throw;
      }

      // destruct and deallocate old buffer
      detail::destroy(first(), last(), allocator());
      allocator().deallocate(first(), capacity_end() - first());

      // update pointers
      first() = new_buffer;
      last() = new_buffer + size;
      capacity_end() = new_buffer + count;
    }

    iterator begin() noexcept
    {
      return iterator{first()};
    }

    const_iterator begin() const noexcept
    {
      return const_iterator{first()};
    }

    iterator end() noexcept
    {
      return iterator{last()};
    }

    const_iterator end() const noexcept
    {
      return const_iterator{last()};
    }

    reverse_iterator rbegin()
    {
      return reverse_iterator{end()};
    }

    const_reverse_iterator rbegin() const
    {
      return const_reverse_iterator{end()};
    }

    reverse_iterator rend()
    {
      return reverse_iterator{begin()};
    }

    const_reverse_iterator rend() const
    {
      return const_reverse_iterator{begin()};
    }

    inline reference operator[](size_type n)
    {
      assert(n < nek::size(*this));
      return *(first() + n);
    }

    inline const_reference operator[](size_type n) const
    {
      assert(n < nek::size(*this));
      return *(first() + n);
    }

    iterator insert(const_iterator position, size_type count, value_type const& value)
    {
      return fill_insert(position, count, value);
    }

    template <class InputIterator>
    iterator insert(const_iterator position, InputIterator first, InputIterator last)
    {
      using tag = typename nek::iterator_traits<InputIterator>::iterator_category;
      insert_(position, first, last, tag{});
      size_type const pos = nek::distance<const_iterator>(begin(), position);
      return begin() + pos;
    }

    template <class... Args>
    iterator emplace(const_iterator position, Args&&... args)
    {
      auto const diff = nek::distance<const_iterator>(begin(), position);
      if (last() == capacity_end()) {
        reserve(larger_size(nek::size(*this)));
      }
      allocator().construct(last(), nek::forward<Args>(args)...);
      ++last();
      nek::rotate(first() + diff, last() - 1, last());
      return begin() + diff;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      if (first == last) {
        return remove_const(first);
      }

      auto f = remove_const(first);
      auto l = remove_const(last);

      iterator new_last = std::move(l, end(), f);
      detail::destroy(new_last.base(), this->last(), allocator());
      this->last() = new_last.base();

      return remove_const(first);
    }

  private:
    static constexpr inline double rate() noexcept
    {
      return 1.5;
    }

    inline size_type larger_size(size_type size) const noexcept
    {
      return nek::max(static_cast<size_type>(size * rate()), size + 1);
    }

    template <class InputIterator>
    void range_initialize(InputIterator first, InputIterator last, std::input_iterator_tag)
    {
      for (; first != last; ++first) {
        nek::emplace_back(*this, *first);
      }
    }

    template <class ForwardIterator>
    void range_initialize(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
    {
      size_type const count = nek::distance(first, last);
      this->first() = allocator().allocate(count);
      this->capacity_end() = this->first() + count;
      this->last() = nek::uninitialized_copy(first, last, this->first(), allocator());
    }

    template <class Iterator>
    void range_initialize(Iterator first, Iterator last)
    {
      using tag = typename nek::iterator_traits<Iterator>::iterator_category;
      range_initialize(first, last, tag{});
    }

    void move_construct(vector&& other, nek::true_type) noexcept
    {
      this->swap(static_cast<vector&>(other));
    }

    void move_construct(vector&& other, nek::false_type) noexcept
    {
      if (other.get_allocator() == this->get_allocator()) {
        move_construct(nek::move(other), nek::true_type{});
      } else {
        range_initialize(
          nek::make_move_iterator(other.begin()),
          nek::make_move_iterator(other.end())
          );
      }
    }

    template <class InputIterator>
    void assign_(InputIterator first, InputIterator last)
    {
      using tag = typename nek::iterator_traits<InputIterator>::iterator_category;
      assign_(first, last, tag{});
    }

    template <class InputIterator>
    void assign_(InputIterator first, InputIterator last, std::input_iterator_tag)
    {
      for (; first != last; ++first) {
        nek::emplace_back(*this, *first);
      }
    }

    template <class ForwardIterator>
    void assign_(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
    {
      size_type const assign_size = nek::distance(first, last);
      if (capacity() < assign_size) {
        allocator().deallocate(this->first(), nek::distance(this->first(), this->capacity_end()));
        size_type const new_capacity_size = larger_size(assign_size);
        this->first() = allocator().allocate(new_capacity_size);
        this->last() = this->first();
        this->capacity_end() = this->first() + count;
      }
      this->last() = nek::uninitialized_copy(first, last, this->first(), get_allocator());
    }

    iterator fill_insert(const_iterator position, size_type count, value_type const& value)
    {
      size_type offset = remove_const(position).base() - first();

      if (count == 0) {
        return begin() + offset;
      }

      // has enough size
      if (count <= static_cast<size_type>(capacity_end() - last())) {
        pointer old_last = last();
        value_type temp = value;
        size_type const position_after_size = static_cast<size_type>(end() - position);
        // position + count is inner of last()
        if (count < position_after_size) {
          // move last elements
          last() = nek::uninitialized_move(last() - count, last(), last());
          // move insert position to backward
          std::copy_backward(remove_const(position).base(), old_last - count, old_last);
          std::fill(remove_const(position).base(), remove_const(position).base() + count, temp);
        } else {
          std::uninitialized_fill_n(
            last(), count - position_after_size, temp/*, get_allocator()*/);
          last() += count - position_after_size;

          nek::uninitialized_move(remove_const(position).base(), old_last, last(), get_allocator());
          last() += position_after_size;

          std::fill(remove_const(position).base(), old_last, temp);
        }
      } else {
        // validate
        if (max_size() - nek::size(*this) < count) {
          throw std::length_error{"nek::vector::insert : count is too large"};
        }
        // allocate new buffer
        size_type const new_capacity_size = larger_size(nek::size(*this) + count);
        pointer new_first = allocator().allocate(new_capacity_size);
        pointer new_last = new_first;
        try {
          std::uninitialized_fill_n(new_first + offset, count, value/*, get_allocator()*/);
          new_last = nullptr;
          
          new_last = nek::uninitialized_copy(
            nek::make_move_if_noexcept_iterator(first()),
            nek::make_move_if_noexcept_iterator(remove_const(position).base()),
            new_first, get_allocator());
          new_last += count;

          new_last = nek::uninitialized_copy(
            nek::make_move_if_noexcept_iterator(remove_const(position).base()),
            nek::make_move_if_noexcept_iterator(last()),
            new_last, get_allocator());
        } catch (...) {
          if (!new_last) {
            nek::detail::destroy(new_first + offset, new_first + offset + count, get_allocator());
          } else {
            nek::detail::destroy(new_first, new_last, get_allocator());
          }
          allocator().deallocate(new_first, new_capacity_size);
          throw;
        }
      }
      return begin() + offset;
    }

    template <class InputIterator>
    void insert_(const_iterator position, InputIterator first, InputIterator last, std::input_iterator_tag)
    {
      size_type const pos = nek::distance(begin(), position);
      size_type const before_size = nek::size(*this);
      try {
        for (; first != last; ++first) {
          emplace(end(), *first);
        }
      } catch (...) {
        erase(begin() + before_size, end());
      }
      nek::rotate(begin() + pos, begin() + before_size, end());
    }

    template <class InputIterator>
    void insert_(const_iterator position, InputIterator first, InputIterator last, std::forward_iterator_tag)
    {
      if (first == last) {
        return;
      }

      size_type const insert_size = nek::distance(first, last);

      // has enough size
      if (insert_size <= static_cast<size_type>(capacity_end() - this->last())) {
        nek::uninitialized_copy(first, last, this->last(), get_allocator());
        nek::rotate(remove_const(position).base(), this->last(), this->last() + insert_size);
        this->last() += insert_size;
      } else {
        // validate
        if (max_size() - nek::size(*this) < insert_size) {
          throw std::length_error{"nek::vector::insert : insert elements size is too large"};
        }

        // allocate new buffer
        size_type const new_capacity_size = larger_size(nek::size(*this) + insert_size);
        pointer new_first = allocator().allocate(new_capacity_size);
        pointer new_last = new_first;
        // move to new buffer from
        // old buffer (before insert position) + insert elements + old buffer (after insert position)
        try {
          new_last = nek::uninitialized_copy(
            nek::make_move_if_noexcept_iterator(this->first()),
            nek::make_move_if_noexcept_iterator(remove_const(position).base()),
            new_first, get_allocator()
            );
          new_last = nek::uninitialized_copy(first, last, new_last, get_allocator());
          new_last = nek::uninitialized_copy(
            nek::make_move_if_noexcept_iterator(remove_const(position).base()),
            nek::make_move_if_noexcept_iterator(this->last()),
            new_last, get_allocator()
            );
        } catch (...) {
          nek::detail::destroy(new_first, new_last, get_allocator());
          allocator().deallocate(new_first, new_capacity_size);
          throw;
        }
        // release old buffer
        nek::detail::destroy(this->first(), this->last(), get_allocator());
        allocator().deallocate(this->first(), nek::distance(this->first(), this->capacity_end()));

        // update pointer
        this->first() = new_first;
        this->last() = new_last;
        this->capacity_end() = new_first + new_capacity_size;
      }
    }

    iterator remove_const(const_iterator it) const
    {
      return iterator(const_cast<pointer>(it.base()));
    }
  };

  template <class T, class Allocator>
  auto size(vector<T, Allocator> const& v) noexcept
  {
    return static_cast<typename vector<T>::size_type>(v.end() - v.begin());
  }
}

#endif
