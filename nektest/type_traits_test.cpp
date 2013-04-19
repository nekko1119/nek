#include "stdafx.h"
#include "CppUnitTest.h"
#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>
#include <nek/type_traits/remove_reference.hpp>
#include <nek/type_traits/is_same.hpp>
#include <nek/type_traits/enable_if.hpp>
#include <nek/type_traits/enabler.hpp>
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
		nek::true_type enable_test_func(T, typename nek::enable_if<nek::is_same<T, int>>::type*& = nek::enabler);

		template <class T>
		nek::false_type enable_test_func(T, typename nek::enable_if<nek::is_same<T, double>>::type*& = nek::enabler);

		TEST_METHOD(enable_if_test)
		{
			using namespace nek;
			int i = 0;
			double d = 0.0;
			static_assert(is_same<decltype(enable_test_func(i)), true_type>::value, "true_type f(T)");
			static_assert(is_same<decltype(enable_test_func(d)), false_type>::value, "false_type f(T)");
		}
	};
}