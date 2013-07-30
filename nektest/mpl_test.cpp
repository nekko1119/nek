#include "stdafx.h"
#include "CppUnitTest.h"
#include <nek/type_traits/is_void.hpp>
#include <nek/type_traits/is_same.hpp>
#include <nek/mpl/bool.hpp>
#include <nek/mpl/identity.hpp>
#include <nek/mpl/if.hpp>
#include <nek/mpl/integral_c.hpp>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nektest
{
    TEST_CLASS(mpl_test)
    {
    public:

        TEST_METHOD(integral_c_test)
        {
            using namespace nek;
            typedef mpl::integral_c<int, 0> zero_type;
            static_assert(zero_type::value == 0, "zero_type::value == 0");
            static_assert(is_same<zero_type::tag, mpl::integral_c_tag>::value, "zero_type::tag == mpl::integral_c_tag");
            static_assert(is_same<zero_type::type, zero_type>::value, "zero_type::type == zero_type");
            static_assert(is_same<zero_type::value_type, int>::value, "zero_type::value_type == int");
            static_assert(is_same<zero_type::next, mpl::integral_c<int, 1>>::value, "zero_type::next == 1");
            static_assert(is_same<zero_type::prior, mpl::integral_c<int, -1>>::value, "zero_type::next == -1");
            Assert::IsTrue(zero_type() == 0, L"zero_type() == 0");
        }

        TEST_METHOD(bool_test)
        {
            using namespace nek;
            static_assert(mpl::true_::value == true, "mpl::true_::value == true");
            static_assert(is_same<mpl::true_::tag, mpl::integral_c_tag>::value, "mpl::true_::tag == mpl::integral_c_tag");
            static_assert(is_same<mpl::true_::type, mpl::true_>::value, "mpl::true_::type == mpl::true_");
            static_assert(is_same<mpl::true_::value_type, bool>::value, "mpl::true_::value_type == bool");
            Assert::IsTrue(mpl::true_() == true, L"mpl::true_() == true");

            static_assert(mpl::false_::value == false, "mpl::false_::value == false");
            static_assert(is_same<mpl::false_::tag, mpl::integral_c_tag>::value, "mpl::false_::tag == mpl::integral_c_tag");
            static_assert(is_same<mpl::false_::type, mpl::false_>::value, "mpl::false_::type == mpl::false_");
            static_assert(is_same<mpl::false_::value_type, bool>::value, "mpl::false_::value_type == bool");
            Assert::IsTrue(mpl::false_() == false, L"mpl::false_() == false");

        }

        TEST_METHOD(identity_test)
        {
            using namespace nek::mpl;
            static_assert(nek::is_same<identity<int>::type, int>::value, "identity<int>::type == int");
            static_assert(nek::is_same<identity<const volatile int>::type, const volatile int>::value, "identity<cv int>::type == cv int");
        }

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