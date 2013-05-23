#ifndef NEK_ANY_HPP
#define NEK_ANY_HPP

#include <stdexcept>
#include <typeinfo>
#include <nek/type_traits/is_reference.hpp>
#include <nek/type_traits/remove_reference.hpp>
#include <nek/utility/swap.hpp>

namespace nek
{
	class any
	{
		template <class T>
		friend T* any_cast(any* pointer);
	public:
		any()
			: held_(nullptr)
		{
		}

		template <class T>
		any(const T& value)
			: held_(new holder<T>(value))
		{
		}

		any(const any& right)
			: held_(right.held_ ? right.held_->clone() : nullptr)
		{
		}

		~any()
		{
			delete held_;
		}

		any& operator=(any right)
		{
			swap(right);
			return *this;
		}

		template <class T>
		any& operator=(const T& value)
		{
			any(value).swap(*this);
			return *this;
		}

		any& swap(any& right)
		{
			nek::swap(held_, right.held_);
			return *this;
		}

		bool empty() const
		{
			return !held_;
		}

		const type_info& type() const
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
			virtual const std::type_info& type() const = 0;
		};

		template <class T>
		class holder
			: public holder_base
		{
		public:
			holder(const T& value)
				:value_(value)
			{
			}

			virtual holder_base* clone() const override final
			{
				return new holder(value_);
			}

			virtual const std::type_info& type() const override final
			{
				return typeid(value_);
			}

			T value_;

		private:
			holder& operator=(const holder&);

		};

		holder_base* held_;
	};

	inline void swap(any& left, any& right)
	{
		left.swap(right);
	}

	class bad_any_cast
		: public std::bad_cast
	{
	public:
		virtual const char* what() const override
		{
			return "nek::bad_any_cast";
		}
	};

	template <class T>
	T* any_cast(any* pointer)
	{
		return pointer && pointer->type() == typeid(T) ?
			&(static_cast<any::holder<T>*>(pointer->held_)->value_) : nullptr;
	}

	template <class T>
	inline const T* any_cast(const any* pointer)
	{
		return any_cast<T>(const_cast<any*>(pointer));
	}

	template <class T>
	T any_cast(any& value)
	{
		typedef typename remove_reference<T>::type nonref_type;
		static_assert(!is_reference<nonref_type>::value, "nek::any_cast : !is_reference<nonref_type>::value");
		
		nonref_type* result = any_cast<nonref_type>(&value);
		if(!result)
		{
			throw bad_any_cast();
		}
		return *result;
	}

	template <class T>
	inline T any_cast(const any& value)
	{
		typedef typename remove_reference<T>::type nonref_type;
		static_assert(!is_reference<nonref_type>::value, "nek::any_cast : !is_reference<nonref_type>::value");

		return any_cast<const nonref_type&>(const_cast<any&>(value));
	}
}

#endif