﻿#include "stdafx.h"
#include "CppUnitTest.h"
#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>
#include <nek/type_traits/remove_reference.hpp>
#include <nek/type_traits/is_same.hpp>
#include <nek/type_traits/enable_if.hpp>
#include <nek/type_traits/is_pointer.hpp>
#include <nek/type_traits/is_integral.hpp>
#include <nek/type_traits/is_void.hpp>
#include <nek/type_traits/is_union.hpp>
#include <nek/type_traits/is_class.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nektest
{
	TEST_CLASS(type_traits_test)
	{
	public:
		TEST_METHOD(integral_constant_test)
		{
			using namespace nek;

			Assert::IsTrue(true_type(), L"true_type == true");
			static_assert(true_type::value == true, "true_type::value == true");
			static_assert(is_same<true_type::value_type, bool>::value, "true_type::value_type == bool");

			Assert::IsTrue(!false_type(), L"false_type == false");
			static_assert(false_type::value == false, "false_type::value == false");
			static_assert(is_same<false_type::value_type, bool>::value, "false_type::value_type == bool");

			typedef integral_constant<int, 0> zero_type;
			Assert::IsTrue(zero_type() == 0, L"integral_constant<int, 0> == 0");
			static_assert(zero_type::value == 0, "integral_constant<int, 0>::value == 0");
			static_assert(is_same<zero_type::value_type, int>::value, "integral_constant<int, 0>::value_type == int");
		}

		TEST_METHOD(remove_cv_test)
		{
			using namespace nek;
			typedef volatile int vint_t;
			static_assert(is_same<remove_volatile<int>::type, int>::value, "remove_volatile<int>::type == int");
			static_assert(is_same<remove_volatile<vint_t>::type, int>::value, "remove_volatile<volatile int>::type == int");
			static_assert(is_same<remove_volatile<const vint_t>::type, const int>::value, "remove_volatile<const volatile int>::type == const int");
			static_assert(is_same<remove_volatile<vint_t*>::type, vint_t*>::value, "remove_volatile<volatile int*>::type == volatille int*");
			static_assert(is_same<remove_volatile<int* volatile>::type, int*>::value, "remove_volatile<int* volatile>::type == int*");
			static_assert(is_same<remove_volatile<vint_t&>::type, vint_t&>::value, "remove_volatile<volatile int&>::type == int&");

			typedef const int cint_t;
			static_assert(is_same<remove_const<int>::type, int>::value, "remove_const<int>::type == int");
			static_assert(is_same<remove_const<cint_t>::type, int>::value, "remove_const<const int>::type == int");
			static_assert(is_same<remove_const<volatile cint_t>::type, volatile int>::value, "remove_const<const volatile int>::type == volatile int");
			static_assert(is_same<remove_const<cint_t*>::type, cint_t*>::value, "remove_const<const int*>::type == const int*");
			static_assert(is_same<remove_const<int* const>::type, int*>::value, "remove_const<int* const>::type == int*");
			static_assert(is_same<remove_const<cint_t&>::type, cint_t&>::value, "remove_const<const int&>::type == int&");

			typedef const volatile int cvint_t;
			static_assert(is_same<remove_cv<int>::type, int>::value, "remove_cv<int>::type == int");
			static_assert(is_same<remove_cv<cvint_t>::type, int>::value, "remove_cv<const volatile int>::type == int");
			static_assert(is_same<remove_cv<cvint_t*>::type, cvint_t*>::value, "remove_cv<const volatile int*>::type == const volatile int*");
			static_assert(is_same<remove_cv<int* const volatile>::type, int*>::value, "remove_cv<int* const volatile>::type == int*");
		}

		TEST_METHOD(remove_reference_test)
		{
			using namespace nek;
			static_assert(is_same<remove_reference<int>::type, int>::value, "remove_reference<int>::type == int");
			static_assert(is_same<remove_reference<int&>::type, int>::value, "remove_reference<int&>::type == int");
			static_assert(is_same<remove_reference<int&&>::type, int>::value, "remove_reference<int&&>::type == int");
			static_assert(is_same<remove_reference<const int&>::type, const int>::value, "remove_reference<const int&>::type == const int");
			static_assert(is_same<remove_reference<int*&>::type, int*>::value, "remove_reference<int*&>::type == int*");
		}

		TEST_METHOD(is_same_test)
		{
			using namespace nek;
			static_assert(is_same<int, int>::value == true, "is_same<int, int>::value");
			static_assert(is_same<int, int&>::value == false, "is_same<int, int&>::value");
			static_assert(is_same<int, const int>::value == false, "is_same<int, const int>::value");
		}

		template <class T>
		typename nek::enable_if<nek::is_same<T, int>, nek::true_type>::type enable_test_func(T);

		template <class T>
		typename nek::enable_if<nek::is_same<T, double>, nek::false_type>::type enable_test_func(T);

		TEST_METHOD(enable_if_test)
		{
			using namespace nek;
			int i = 0;
			double d = 0.0;
			static_assert(is_same<decltype(enable_test_func(i)), true_type>::value, "true_type f(T)");
			static_assert(is_same<decltype(enable_test_func(d)), false_type>::value, "false_type f(T)");
		}

		TEST_METHOD(is_pointer_test)
		{
			using namespace nek;
			static_assert(is_pointer<int*>::value == true, "is_pointer<int*>::value == true");
			static_assert(is_same<is_pointer<int*>::value_type, bool>::value, "is_same<is_pointer<int*>::value_type, bool>::value");
			Assert::IsTrue(is_pointer<int*>() == true, L"is_pointer<int*>() ==true");
			static_assert(is_pointer<int**>::value == true, "is_pointer<int**>::value == true");
			static_assert(is_pointer<int>::value == false, "is_pointer<int>::value == false");
			static_assert(is_pointer<int*&>::value == false, "is_pointer<int*&>::value == false");
			static_assert(is_pointer<int[]>::value == false, "is_pointer_<int[]>::value == false");
			static_assert(is_pointer<void (*)()>::value == true, "is_pointer<void (*)()>::value == true");
			static_assert(is_pointer<void ()>::value == false, "is_pointer<void ()>::value == true");
			static_assert(is_pointer<std::nullptr_t>::value == false, "is_pointer<std::nullptr_t>::value == false");

			struct is_pointer_test_class
			{
				void mem_fn(){}
				int mem;
			};

			static_assert(is_pointer<void (is_pointer_test_class::*)()>::value == false, "is_pointer<void (is_pointer_test_class::*)()>::value == false");
			static_assert(is_pointer<int (is_pointer_test_class::*)>::value == false, "is_pointer<int (is_pointer_test_class::*)>::value == false");
		}

		TEST_METHOD(is_integral_test)
		{
			using namespace nek;
			static_assert(is_integral<int>::value == true, "is_integral<int>::value == true");
			static_assert(is_same<is_integral<int>::value_type, bool>::value, "is_integral<int>:value_type == bool");
			Assert::IsTrue(is_integral<int>() == true, L"is_integral<int>() == true");
			static_assert(is_integral<int*>::value == false, "is_integral<int*>::value == false");
			static_assert(is_integral<char>::value == true, "is_integral<char>::value == true");
			static_assert(is_integral<const volatile unsigned long long int>::value == true, "is_integral<const volatile unsigned long long int>::value == true");
			enum class is_integral_test_enum : unsigned int
			{
			};
			static_assert(is_integral<is_integral_test_enum>::value == false, "is_integral<is_integral_test_enum>::value == false");
			static_assert(is_integral<int&>::value == false, "is_integral<int&>::value == false");
			static_assert(is_integral<int ()>::value == false, "is_integral<int ()>::value == false");
			static_assert(is_integral<int []>::value == false, "is_integral<int []>::value == false");
			static_assert(is_integral<float>::value == false, "is_integral<float>::value == false");
		}

		TEST_METHOD(is_void_test)
		{
			using namespace nek;
			static_assert(is_void<void>::value == true, "is_void<void>::value == true");
			static_assert(is_same<is_void<void>::value_type, bool>::value, "is_void<void>:value_type == bool");
			Assert::IsTrue(is_void<void>() == true, L"is_integral<int>() == true");
			static_assert(is_void<int>::value == false, "is_void<int>::value == false");
			static_assert(is_void<const volatile void>::value == true, "is_void<const volatile void>::value == true");
			static_assert(is_void<void*>::value == false, "is_void<void*>::value == false");
			static_assert(is_void<void ()>::value == false, "is_void<void ()>::value == false");
		}

		TEST_METHOD(is_union_test)
		{
			using namespace nek;
			union is_union_test_union
			{
			};
			struct is_union_test_struct
			{
			};

			static_assert(is_union<is_union_test_union>::value == true, "is_union<is_union_test_union>::value == true");
			static_assert(is_same<is_union<is_union_test_union>::value_type, bool>::value,"is_union<is_union_test_union>::value_type == bool");
			Assert::IsTrue(is_union<is_union_test_union>() == true, L"is_union<is_union_test_union>() == true");
			static_assert(is_union<const volatile is_union_test_union>::value == true, "is_union<const volatile is_union_test_union>::value == true");
			static_assert(is_union<int>::value == false, "is_union<int>::value == false");
			static_assert(is_union<is_union_test_struct>::value == false, "is_union<is_union_test_struct>::value == false");
			static_assert(is_union<is_union_test_union*>::value == false, "is_union<is_union_test_union*>::value == false");
			static_assert(is_union<is_union_test_union&>::value == false, "is_union<is_union_test_union&>::value == false");
			static_assert(is_union<is_union_test_union ()>::value == false, "is_union<is_union_test_union ()>::value == false");
			static_assert(is_union<is_union_test_union []>::value == false, "is_union<is_union_test_union []>::value == false");
		}

		TEST_METHOD(is_class_test)
		{
			using namespace nek;
			union is_class_test_union
			{
			};
			class is_class_test_class
			{
			};

			static_assert(is_class<is_class_test_class>::value == true, "is_class<is_class_test_class>::value == true");
			static_assert(is_same<is_union<is_class_test_class>::value_type, bool>::value,"is_class<is_class_test_class>::value_type == bool");
			Assert::IsTrue(is_class<is_class_test_class>() == true, L"is_class<is_class_test_class>() == true");
			static_assert(is_class<const volatile is_class_test_class>::value == true, "is_class<const volatile is_class_test_class>::value == true");
			static_assert(is_class<int>::value == false, "is_class<int>::value == false");
			static_assert(is_class<is_class_test_union>::value == false, "is_class<is_class_test_union>::value == false");
			static_assert(is_class<is_class_test_class*>::value == false, "is_class<is_class_test_class*>::value == false");
			static_assert(is_class<is_class_test_class&>::value == false, "is_class<is_class_test_class&>::value == false");
			static_assert(is_class<is_class_test_class ()>::value == false, "is_class<is_class_test_class ()>::value == false");
			static_assert(is_class<is_class_test_class []>::value == false, "is_class<is_class_test_class []>::value == false");
		}
	};
}