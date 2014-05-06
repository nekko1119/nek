#ifndef NEK_ANY_ANY_HPP
#define NEK_ANY_ANY_HPP

#include <nek/any/any_fwd.hpp>
#include <nek/any/exception.hpp>
#include <nek/type_traits/is_reference.hpp>
#include <nek/type_traits/remove_reference.hpp>
#include <nek/utility/swap.hpp>

namespace nek
{
  class any
  {
  public:
    any() = default;

    template <class T>
    any(T const& value)
      : held_(new holder<T>(value))
    {
    }

    any(any const& right)
      : held_(right.held_ ? right.held_->clone() : nullptr)
    {
    }

    ~any()
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

    any& swap(any& right)
    {
      using nek::swap;
      swap(held_, right.held_);
      return *this;
    }

    bool is_empty() const
    {
      return !held_;
    }

    bool empty() const
    {
      return is_empty();
    }

    type_info const& type() const
    {
      return held_ ? held_->type() : typeid(void);
    }

  private:
    class holder_base
    {
    public:
      virtual ~holder_base()
      {
      }

      virtual holder_base* clone() const = 0;
      virtual std::type_info const& type() const = 0;
    };

    template <class T>
    class holder
      : public holder_base
    {
    public:
      holder(const T& value)
        : value_(value)
      {
      }

      holder_base* clone() const override
      {
        return new holder(value_);
      }

      std::type_info const& type() const override
      {
        return typeid(value_);
      }

      T value_;

    private:
      holder& operator=(holder const&) = delete;

    };

    holder_base* held_ = nullptr;

  private:
    template <class T>
    friend T* any_cast(any* pointer);
  };

  inline void swap(any& left, any& right)
  {
    left.swap(right);
  }

  template <class T>
  T* any_cast(any* pointer)
  {
    return pointer && pointer->type() == typeid(T) ?
      &(static_cast<any::holder<T>*>(pointer->held_)->value_) : nullptr;
  }

  template <class T>
  inline T const* any_cast(any const* pointer)
  {
    return any_cast<T>(const_cast<any*>(pointer));
  }

  template <class T>
  T any_cast(any& value)
  {
    using nonref_type = typename remove_reference<T>::type;
    static_assert(!is_reference<nonref_type>::value, "nek::any_cast : !is_reference<nonref_type>::value");

    nonref_type* result = any_cast<nonref_type>(&value);
    if (!result) {
      throw bad_any_cast_exception();
    }
    return *result;
  }

  template <class T>
  inline T any_cast(any const& value)
  {
    using nonref_type = typename remove_reference<T>::type;
    static_assert(!is_reference<nonref_type>::value, "nek::any_cast : !is_reference<nonref_type>::value");

    return any_cast<nonref_type const&>(const_cast<any&>(value));
  }
}

#endif