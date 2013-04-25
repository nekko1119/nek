#include "stdafx.h"
#include "CppUnitTest.h"
#include <nek/type_traits/is_void.hpp>
#include <nek/type_traits/is_same.hpp>
#include <nek/mpl/if.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nektest
{
	TEST_CLASS(mpl_test)
	{
	public:
		
		TEST_METHOD(if_test)
		{
			using namespace nek::mpl;
			static_assert(nek::is_same<if_c<true, char, double>::type, char>::value, "if_c<true, char, double>::type == char");
			static_assert(nek::is_same<if_c<false, char, double>::type, double>::value, "if_c<false, char, double>::type == double");
			static_assert(nek::is_same<if_<nek::is_void<void>, char, double>::type, char>::value, "if_<is_void<void>, char, double> == char");
			static_assert(nek::is_same<if_<nek::is_void<int>, char, double>::type, double>::value, "if_<is_void<int>, char, double> == double");
		}
	};
}