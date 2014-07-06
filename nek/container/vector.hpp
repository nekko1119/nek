#include <nek/container/detail/destroy.hpp>
#include <nek/allocator/allocator.hpp>
#include <nek/allocator/allocator_traits.hpp>
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
      using pointer = typename nek::allocator_traits<base_type>::pointer;

      pointer first_; // head pointer to reserved and initialized storage
      pointer last_; // initialized storage end
      pointer end_; // reserved storage end

      alloc_type allocator()
      {
        return *(static_cast<alloc_type*>(this));
      }

    public:
      vector_base()
        : base_type(),
        first_(nullptr),
        last_(nullptr),
        end_(nullptr)
      {
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
    using size_type = typename alloc_traits::size_type;
    using difference_type = typename alloc_traits::difference_type;
    using reference = T&;
    using const_reference = T const&;
    using pointer = typename base_type::pointer;
    using const_pointer = typename alloc_traits::const_pointer;

    vector()
      : base_type{}
    {
    }

    ~vector()
    {
      container_detail::destroy(first_, last_, allocator());
    }
  };
}