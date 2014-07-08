#ifndef NEK_ANY_ANY_HPP
#define NEK_ANY_ANY_HPP

#include <nek/any/any_fwd.hpp>
#include <nek/any/exception.hpp>
#include <nek/mpl/if.hpp>
// TODO : add_reference
#include <type_traits>
#include <nek/type_traits/is_reference.hpp>
#include <nek/type_traits/remove_reference.hpp>
#include <nek/utility/swap.hpp>

namespace nek
{
  class any
  {
  private:
    class holder_base
    {
    public:
      holder_base() = default;
      holder_base(holder_base const&) = default;

      virtual ~holder_base()
      {
      }

      virtual holder_base* clone() const = 0;
      virtual std::type_info const& type() const noexcept = 0;
    };

    template <class T>
    class holder
      : public holder_base
    {
    public:
      T value_;

      holder(const T& value)
        : value_(value)
      {
      }

      holder& operator=(holder const&) = delete;

      holder_base* clone() const override
      {
        return new holder(value_);
      }

      std::type_info const& type() const noexcept override
      {
        return typeid(value_);
      }
    };

    holder_base* held_ = nullptr;

  public:
    any() noexcept = default;

    template <class T>
    any(T const& value)
      : held_(new holder<T>(value))
    {
    }

    any(any const& right)
      : held_(right.held_ ? right.held_->clone() : nullptr)
    {
    }

    ~any() noexcept
    {
      delete held_;
      held_ = nullptr;
    }

    any& operator=(any const& right)
    {
      any(right).swap(*this);
      return *this;
    }

    template <class T>
    any& operator=(T const& value)
    {
      any(value).swap(*this);
      return *this;
    }

    any& swap(any& right) noexcept
    {
      using nek::swap;
      swap(held_, right.held_);
      return *this;
    }

    bool is_empty() const noexcept
    {
      return !held_;
    }

    type_info const& type() const noexcept
    {
      return held_ ? held_->type() : typeid(void);
    }

  private:
    template <class T>
    friend T* any_cast(any* pointer) noexcept;
  };

  inline void swap(any& left, any& right) noexcept
  {
    left.swap(right);
  }

  inline void clear(any& value) noexcept
  {
    any{}.swap(value);
  }

  template <class T>
  T* any_cast(any* pointer) noexcept
  {
    return pointer && pointer->type() == typeid(T) ?
      &(static_cast<any::holder<T>*>(pointer->held_)->value_) : nullptr;
  }

  template <class T>
  inline T const* any_cast(any const* pointer) noexcept
  {
    return any_cast<T>(const_cast<any*>(pointer));
  }

  template <class T>
  T any_cast(any& value)
  {
    using nonref_type = remove_reference_t<T>;
    using ref_type = nek::mpl::if_t<nek::is_reference<T>,
      T, typename std::add_reference<T>::type>;

    nonref_type* result = any_cast<nonref_type>(&value);
    if (!result) {
      throw bad_any_cast_exception();
    }
    return static_cast<ref_type>(*result);
  }

  template <class T>
  inline T any_cast(any const& value)
  {
    using nonref_type = remove_reference_t<T>
    return any_cast<nonref_type const&>(const_cast<any&>(value));
  }
}

#endif