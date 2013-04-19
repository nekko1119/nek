#include "stdafx.h"
#include "CppUnitTest.h"
#include <nek/type_traits/integral_constant.hpp>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nektest
{
	TEST_CLASS(type_traits_test)
	{
	public:
		TEST_METHOD(integral_constant_test)
		{
			using namespace nek;

			Assert::IsTrue(true_type() == true);
			Assert::IsTrue(true_type::value == true);
			Assert::IsTrue(typeid(true_type::value_type) == typeid(bool));

			Assert::IsTrue(false_type() == false);
			Assert::IsTrue(false_type::value == false);
			Assert::IsTrue(typeid(false_type::value_type) == typeid(bool));

			typedef integral_constant<int, 0> zero_type;
			Assert::IsTrue(zero_type() == 0);
			Assert::IsTrue(zero_type::value == 0);
			Assert::IsTrue(typeid(zero_type::value_type) == typeid(int));
		}
	};
}