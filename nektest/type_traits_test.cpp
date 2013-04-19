//TODO : 後でIsTrueとtypeidを使っているところをis_same実装したらis_sameとstatic_assertに直す
#include "stdafx.h"
#include "CppUnitTest.h"
#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nektest
{
	TEST_CLASS(type_traits_test)
	{
	public:
		TEST_METHOD(integral_constant_test)
		{
			using namespace nek;

			Assert::IsTrue(true_type() == true, L"true_type == true");
			Assert::IsTrue(true_type::value == true, L"true_type::value == true");
			Assert::IsTrue(typeid(true_type::value_type) == typeid(bool), L"true_type::value_type == bool");

			Assert::IsTrue(false_type() == false, L"false_type == false");
			Assert::IsTrue(false_type::value == false, L"false_type::value == false");
			Assert::IsTrue(typeid(false_type::value_type) == typeid(bool), L"false_type::value_type == bool");

			typedef integral_constant<int, 0> zero_type;
			Assert::IsTrue(zero_type() == 0, L"integral_constant<int, 0> == 0");
			Assert::IsTrue(zero_type::value == 0, L"integral_constant<int, 0>::value == 0");
			Assert::IsTrue(typeid(zero_type::value_type) == typeid(int), L"integral_constant<int, 0>::value_type == int");
		}

		TEST_METHOD(remove_cv_test)
		{
			using namespace nek;
			typedef volatile int vint_t;
			Assert::IsTrue(typeid(remove_volatile<int>::type) == typeid(int), L"remove_volatile<int>::type == int");
			Assert::IsTrue(typeid(remove_volatile<vint_t>::type) == typeid(int), L"remove_volatile<volatile int>::type == int");
			Assert::IsTrue(typeid(remove_volatile<const vint_t>::type) == typeid(const int), L"remove_volatile<const volatile int>::type == const int");
			Assert::IsTrue(typeid(remove_volatile<vint_t*>::type) == typeid(vint_t*), L"remove_volatile<volatile int*>::type == volatille int*");
			Assert::IsTrue(typeid(remove_volatile<int* volatile>::type) == typeid(int*), L"remove_volatile<int* volatile>::type == int*");
			Assert::IsTrue(typeid(remove_volatile<vint_t&>::type) == typeid(int&), L"remove_volatile<volatile int&>::type == int&");

			typedef const int cint_t;
			Assert::IsTrue(typeid(remove_const<int>::type) == typeid(int), L"remove_const<int>::type == int");
			Assert::IsTrue(typeid(remove_const<cint_t>::type) == typeid(int), L"remove_const<const int>::type == int");
			Assert::IsTrue(typeid(remove_const<volatile cint_t>::type) == typeid(volatile int), L"remove_const<const volatile int>::type == volatile int");
			Assert::IsTrue(typeid(remove_const<cint_t*>::type) == typeid(cint_t*), L"remove_const<const int*>::type == const int*");
			Assert::IsTrue(typeid(remove_const<int* const>::type) == typeid(int*), L"remove_const<int* const>::type == int*");
			Assert::IsTrue(typeid(remove_const<cint_t&>::type) == typeid(int&), L"remove_const<const int&>::type == int&");

			typedef const volatile int cvint_t;
			Assert::IsTrue(typeid(remove_cv<int>::type) == typeid(int), L"remove_cv<int>::type == int");
			Assert::IsTrue(typeid(remove_cv<cvint_t>::type) == typeid(int), L"remove_cv<const volatile int>::type == int");
			Assert::IsTrue(typeid(remove_cv<cvint_t*>::type) == typeid(cvint_t*), L"remove_cv<const volatile int*>::type == const volatile int*");
			Assert::IsTrue(typeid(remove_cv<int* const volatile>::type) == typeid(int*), L"remove_cv<int* const volatile>::type == int*");
		}
	};
}