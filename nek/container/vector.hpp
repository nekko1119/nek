#include <nek/detail/destroy.hpp>
#include <nek/allocator/allocator.hpp>
#include <nek/allocator/allocator_traits.hpp>
#include <nek/uninitialized/unitiliazed_default.hpp>
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
      using alloc_type = base_type; // TODO : workaround. base_type::base_type is not allowed.
      using pointer = typename nek::allocator_traits<alloc_type>::pointer;
      using size_type = typename nek::allocator_traits<alloc_type>::size_type;

      pointer first_; // head pointer to reserved and initialized storage
      pointer last_; // initialized storage end
      pointer end_; // reserved storage end

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
        end_{nullptr}
      {
      }

      explicit vector_base(Allocator const& allocator)
        : base_type{allocator},
        first_{nullptr},
        last_{nullptr},
        end_{nullptr}
      {
      }

      explicit vector_base(size_type count)
        : base_type{}
      {
        first_ = base_type::allocate(count);
        last_ = first_;
        end_ = first_ + count;
      }

      ~vector_base()
      {
        if (first_) {
          base_type::deallocate(first_, end_ - last_);
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
      nek::uninitialized_default_n(first_, count, allocator());
      last_ = end_;
    }

    ~vector()
    {
      detail::destroy(first_, last_, allocator());
    }

    allocator_type get_allocator() const noexcept
    {
      return allocator_type{allocator()};
    }

    size_type size() const noexcept
    {
      return static_cast<size_type>(last_ - first_);
    }
  };
}