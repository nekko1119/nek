﻿#ifndef NEK_CONTAINER_VECTOR_HPP
#define NEK_CONTAINER_VECTOR_HPP

#include <stdexcept>
#include <iostream> // debug

#include <nek/container/function.hpp>
#include <nek/detail/destroy.hpp>
#include <nek/allocator/allocator.hpp>
#include <nek/allocator/allocator_traits.hpp>
#include <nek/iterator/move_iterator.hpp>
#include <nek/iterator/normal_iterator.hpp>
#include <nek/uninitialized/uninitialized_copy.hpp>
#include <nek/uninitialized/uninitialized_default.hpp>
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
        first_ = base_type::allocate(count);
        last_ = first_;
        capacity_end_ = first_ + count;
      }

      ~vector_base()
      {
        if (first_) {
          base_type::deallocate(first_, capacity_end_ - last_);
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

      // debug
      std::cout << "before :\n";
      for (auto i = first(); i != capacity_end(); ++i) {
        std::cout << *i << std::endl;
      }

      // destruct and deallocate old buffer
      detail::destroy(first(), last(), allocator());
      allocator().deallocate(first(), capacity_end() - first());

      // update pointers
      first() = new_buffer;
      last() = new_buffer + size;
      capacity_end() = new_buffer + count;

      // debug
      std::cout << "after :\n";
      for (auto i = first(); i != capacity_end(); ++i) {
        std::cout << *i << std::endl;
      }
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

    reference operator[](size_type n)
    {
      return *(first() + n);
    }

    const_reference operator[](size_type n) const
    {
      return *(first() + n);
    }
  };

  template <class T, class Allocator>
  bool is_empty(vector<T, Allocator> const& v) noexcept
  {
    return v.begin() == v.end();
  }

  template <class T, class Allocator>
  auto size(vector<T, Allocator> const& v) noexcept
  {
    return static_cast<typename vector<T>::size_type>(v.end() - v.begin());
  }
}

#endif