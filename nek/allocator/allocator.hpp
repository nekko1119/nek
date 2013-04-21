#ifndef NEK_ALLOCATOR_ALLOCATOR_HPP
#define NEK_ALLOCATOR_ALLOCATOR_HPP

#include <cstddef>
#include <nek/type_traits/remove_cv.hpp>
#include <nek/utility/addressof.hpp>

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

		pointer* allocate(size_type count, const void* = nullptr) const
		{
			void* ptr = nullptr;
			if(0U < count && count < max_size())
			{
				ptr = ::operator new(count * sizeof(value_type));
			}
			return static_cast<pointer>(ptr);
		}

		void deallocate(pointer ptr, size_type) const
		{
			::operator delete(ptr);
		}

		inline pointer address(reference value) const
		{
			return addressof(value);
		}

		inline const_pointer addressof(const_reference value) const
		{
			return addressof(value);
		}

		inline size_type max_size() const
		{
			return static_cast<size_type>(-1) / sizeof(value_type);
		}
	};
}

#endif