#include <nek/allocator/allocator_traits.hpp>
#include <gtest/gtest.h>
#include "../type_traits/static_assert.hpp"
#include <nek/allocator/allocator.hpp>

namespace
{
	template <class T>
	struct minimum_allocator
	{
		using value_type = T;

		minimum_allocator() = default;

		template <class U>
		minimum_allocator(minimum_allocator<U> const&)
		{
		}

		T* allocate(std::size_t count)
		{
			return new T[count];
		}

		void deallocate(T* p, std::size_t)
		{
			delete[] p;
		}
	};

	template <class T, class U>
	bool operator==(minimum_allocator<T> const&, minimum_allocator<U> const&)
	{
		return true;
	}

	template <class T, class U>
	bool operator!=(minimum_allocator<T> const&, minimum_allocator<U> const&)
	{
		return false;;
	}
}

TEST(allocator_traits_test, allocator_member_type)
{
	using actual = nek::allocator_traits<nek::allocator<int>>;
	using expect = nek::allocator<int>;
	STATIC_ASSERT_EQ(actual::allocator_type, expect);
	STATIC_ASSERT_EQ(actual::value_type, expect::value_type);
	STATIC_ASSERT_EQ(actual::pointer, expect::pointer);
	STATIC_ASSERT_EQ(actual::const_pointer, expect::const_pointer);
	STATIC_ASSERT_EQ(actual::void_pointer, expect::rebind<void>::other::pointer);
	STATIC_ASSERT_EQ(actual::const_void_pointer, expect::rebind<void>::other::const_void_pointer);
	STATIC_ASSERT_EQ(actual::difference_type, expect::difference_type);
	STATIC_ASSERT_EQ(actual::size_type, expect::size_type);
	STATIC_ASSERT_EQ(actual::propagate_on_container_copy_assignment, nek::false_type);
	STATIC_ASSERT_EQ(actual::propagate_on_container_move_assignment, nek::false_type);
	STATIC_ASSERT_EQ(actual::propagate_on_container_swap, nek::false_type);
	STATIC_ASSERT_EQ(actual::rebind_alloc<char>, expect::rebind<char>::other);
	STATIC_ASSERT_EQ(actual::rebind_traits<char>, nek::allocator_traits<nek::allocator<char>>);
}

TEST(allocator_traits_test, allocate_construct_destroy_deallocate)
{
	nek::allocator<int> alloc;
	using type = nek::allocator_traits<nek::allocator<int>>;
	int* actual = type::allocate(alloc, 3);
	type::construct(alloc, &actual[1], 42);
	EXPECT_EQ(42, actual[1]);
	type::destroy(alloc, actual);
	type::deallocate(alloc, actual, 3);
}

TEST(allocator_traits_test, max_size)
{
	nek::allocator<int> alloc;
	using type = nek::allocator_traits<nek::allocator<int>>;
	EXPECT_EQ(alloc.max_size(), type::max_size(alloc));
}

TEST(allocator_triats_test, select_on_container_copy_construction)
{
	nek::allocator<int> alloc;
	using type = nek::allocator_traits<nek::allocator<int>>;
	EXPECT_EQ(alloc, type::select_on_container_copy_construction(alloc));
}

TEST(allocator_traits_test, minimum_allocator_member_type)
{
	using type = nek::allocator_traits<minimum_allocator<int>>;
	STATIC_ASSERT_EQ(type::allocator_type, minimum_allocator<int>);
	STATIC_ASSERT_EQ(type::value_type, int);
	STATIC_ASSERT_EQ(type::pointer, int*);
	STATIC_ASSERT_EQ(type::const_pointer, int const*);
	STATIC_ASSERT_EQ(type::void_pointer, void*);
	STATIC_ASSERT_EQ(type::const_void_pointer, void const*);
	STATIC_ASSERT_EQ(type::difference_type, std::ptrdiff_t);
	STATIC_ASSERT_EQ(type::size_type, std::size_t);
	STATIC_ASSERT_EQ(type::propagate_on_container_copy_assignment, nek::false_type);
	STATIC_ASSERT_EQ(type::propagate_on_container_move_assignment, nek::false_type);
	STATIC_ASSERT_EQ(type::propagate_on_container_swap, nek::false_type);
	STATIC_ASSERT_EQ(type::rebind_alloc<char>, minimum_allocator<char>);
	STATIC_ASSERT_EQ(type::rebind_traits<char>, nek::allocator_traits<minimum_allocator<char>>);
}

TEST(allocator_traits_test, minimum_allocate_construct_destroy_deallocate)
{
	minimum_allocator<int> alloc;
	using type = nek::allocator_traits<minimum_allocator<int>>;
	int* actual = type::allocate(alloc, 3);
	type::construct(alloc, &actual[1], 42);
	EXPECT_EQ(42, actual[1]);
	type::destroy(alloc, actual);
	type::deallocate(alloc, actual, 3);
}

TEST(allocator_traits_test, minimum_max_size)
{
	minimum_allocator<int> alloc;
	using type = nek::allocator_traits<minimum_allocator<int>>;
	EXPECT_EQ(std::numeric_limits<type::size_type>::max(), type::max_size(alloc));
}

TEST(allocator_triats_test, minimum_select_on_container_copy_construction)
{
	minimum_allocator<int> alloc;
	using type = nek::allocator_traits<minimum_allocator<int>>;
	EXPECT_EQ(alloc, type::select_on_container_copy_construction(alloc));
}