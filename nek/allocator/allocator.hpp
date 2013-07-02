#ifndef NEK_ALLOCATOR_ALLOCATOR_HPP
#define NEK_ALLOCATOR_ALLOCATOR_HPP

#include <cstddef>
#include <exception>
#include <new>
#include <nek/type_traits/remove_cv.hpp>
#include <nek/utility/addressof.hpp>
#include <nek/utility/forward.hpp>

namespace nek
{
	template <class T>
	class allocator
	{
	public:
		typedef typename remove_cv<T>::type value_type;
		typedef value_type* pointer;
		typedef value_type& reference;
		typedef const pointer const_pointer;
		typedef const reference const_reference;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

		template <class U>
		struct rebind
		{
			typedef allocator<U> other;
		};

		allocator()
		{
		}

		allocator(const allocator<T>&)
		{
		}

		template <class U>
		allocator(const allocator<U>&)
		{
		}

		template <class U>
		allocator<T>& operator=(const allocator<U>&)
		{
			return *this;
		}

		pointer allocate(size_type count, const void* = nullptr) const
		{
			void* ptr = nullptr;
			if(count < 1U || max_size() < count || (ptr = ::operator new(count * sizeof(value_type))) == nullptr)
			{
				throw std::bad_alloc();
			}
			return static_cast<pointer>(ptr);
		}

		void deallocate(pointer ptr, size_type) const
		{
			::operator delete(ptr);
		}

		template <class U, class... Args>
		void construct(U* other, Args&&... args) const
		{
			::new (reinterpret_cast<void*>(other)) U(forward<Args>(args)...);
		}

		template <class U>
		void destroy(U* other) const
		{
			other->~U();
		}

		inline pointer address(reference value)
		{
			return addressof(value);
		}

		inline const_pointer address(const_reference value) const
		{
			return addressof(value);
		}

		inline size_type max_size() const
		{
			return static_cast<size_type>(-1) / sizeof(value_type);
		}
	};

	template <>
	class allocator<void>
	{
	public:
		typedef void value_type;
		typedef value_type* pointer;
		typedef value_type* void_pointer;
		typedef const pointer const_pointer;
		typedef const void_pointer const_void_pointer;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;

		template <class U>
		struct rebind
		{
			typedef allocator<U> other;
		};

		allocator()
		{
		}

		allocator(const allocator<void>&)
		{
		}

		template <class U>
		allocator(const allocator<U>&)
		{
		}

		template <class U>
		allocator<void>& operator=(const allocator<U>&)
		{
			return *this;
		}
	};

	template <class T, class U>
	inline bool operator==(const allocator<T>&, const allocator<U>&)
	{
		return true;
	}

	template <class T, class U>
	inline bool operator!=(const allocator<T>& left, const allocator<U>& right)
	{
		return !(left == right);
	}
}

#endif