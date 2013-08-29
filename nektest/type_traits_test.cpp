#include "stdafx.h"
#include "CppUnitTest.h"
#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/remove_cv.hpp>
#include <nek/type_traits/remove_reference.hpp>
#include <nek/type_traits/is_same.hpp>
#include <nek/type_traits/enable_if.hpp>
#include <nek/type_traits/has_difference_type.hpp>
#include <nek/type_traits/has_element_type.hpp>
#include <nek/type_traits/has_iterator.hpp>
#include <nek/type_traits/has_pointer.hpp>
#include <nek/type_traits/has_type.hpp>
#include <nek/type_traits/has_value_type.hpp>
#include <nek/type_traits/add_cv.hpp>
#include <nek/type_traits/is_const.hpp>
#include <nek/type_traits/is_enum.hpp>
#include <nek/type_traits/is_pointer.hpp>
#include <nek/type_traits/is_volatile.hpp>
#include <nek/type_traits/is_integral.hpp>
#include <nek/type_traits/is_void.hpp>
#include <nek/type_traits/is_union.hpp>
#include <nek/type_traits/is_class.hpp>
#include <nek/type_traits/is_lvalue_reference.hpp>
#include <nek/type_traits/is_rvalue_reference.hpp>
#include <nek/type_traits/is_reference.hpp>
#include <nek/type_traits/is_floating_point.hpp>
#include <nek/type_traits/make_unsigned.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define NEK_STRINGIZE(str) #str
#define NEK_HAS_XXX_TEST_METHOD(xxx)\
TEST_METHOD(has_##xxx##_test)\
{\
    using namespace nek;\
    struct yes\
    {\
        typedef int xxx;\
    };\
    struct no\
    {\
        int xxx;\
    };\
    static_assert(has_##xxx##<yes>::value, NEK_STRINGIZE(has_##xxx##<yes> == true));\
    static_assert(!has_##xxx##<no>::value, NEK_STRINGIZE(has_##xxx##<no> == false)); \
}


namespace nektest
{
    TEST_CLASS(type_traits_test)
    {
    public:
        TEST_METHOD(integral_constant_test)
        {
            using namespace nek;

            Assert::IsTrue(true_type(), L"true_type == true");
            static_assert(is_same<true_type::type, true_type>::value, "true_type::type == true_type");
            static_assert(true_type::value == true, "true_type::value == true");
            static_assert(is_same<true_type::value_type, bool>::value, "true_type::value_type == bool");

            Assert::IsTrue(!false_type(), L"false_type == false");
            static_assert(is_same<false_type::type, false_type>::value, "false_type::type == false_type");
            static_assert(false_type::value == false, "false_type::value == false");
            static_assert(is_same<false_type::value_type, bool>::value, "false_type::value_type == bool");

            typedef integral_constant<int, 0> zero_type;
            Assert::IsTrue(zero_type() == 0, L"integral_constant<int, 0> == 0");
            static_assert(is_same<zero_type::type, zero_type>::value, "zero_type::type == zero_type");
            static_assert(zero_type::value == 0, "integral_constant<int, 0>::value == 0");
            static_assert(is_same<zero_type::value_type, int>::value, "integral_constant<int, 0>::value_type == int");
        }

        TEST_METHOD(add_cv_test)
        {
            using namespace nek;
            static_assert(is_const<add_const<int>::type>::value, "add_const<int> == const int");
            static_assert(is_const<add_const<const int>::type>::value, "add_const<const int> == const int");
            static_assert(is_const<add_const<const int*>::type>::value, "add_const<const int*> == const int* const");
            static_assert(is_const<add_const<int* const>::type>::value, "add_const<int* const> == int* const");
            static_assert(!is_const<add_const<const int&>::type>::value, "add_const<const int&> != const type");

            static_assert(is_volatile<add_volatile<int>::type>::value, "add_volatile<int> == volatile int");
            static_assert(is_volatile<add_volatile<volatile int>::type>::value, "add_volatile<volatile int> == volatile int");
            static_assert(is_volatile<add_volatile<volatile int*>::type>::value, "add_volatile<volatile int*> == volatile int* volatile");
            static_assert(is_volatile<add_volatile<int* volatile>::type>::value, "add_volatile<int* volatile> == int* volatile");
            static_assert(!is_volatile<add_volatile<volatile int&>::type>::value, "add_volatile<volatile int&> != volatile type");

            typedef const volatile int cv_int;
            static_assert(is_same<add_cv<int>::type, cv_int>::value, "add_cv<int> == cv int");
            static_assert(is_same<add_cv<const int>::type, cv_int>::value, "add_cv<const int> == cv int");
            static_assert(is_same<add_cv<volatile int>::type, cv_int>::value, "add_cv<volatile int> == cv int");
            static_assert(is_same<add_cv<const volatile int>::type, cv_int>::value, "add_cv<const volatile int> == cv int");
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
            static_assert(is_same<is_same<int, int>::type, true_type>::value, "is_same<True>::type == true_type");
            static_assert(is_same<int, int>::value == true, "is_same<int, int>::value");
            static_assert(is_same<is_same<int, int&>::type, false_type>::value, "is_same<False>::type == false_type");
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

        NEK_HAS_XXX_TEST_METHOD(difference_type)
        NEK_HAS_XXX_TEST_METHOD(element_type)
        NEK_HAS_XXX_TEST_METHOD(iterator)
        NEK_HAS_XXX_TEST_METHOD(pointer)
        NEK_HAS_XXX_TEST_METHOD(type)
        NEK_HAS_XXX_TEST_METHOD(value_type)

        TEST_METHOD(is_const_test)
        {
            using namespace nek;
            static_assert(is_const<const int>::value == true, "is_const<const int>::value == true");
            static_assert(is_same<is_const<const int>::value_type, bool>::value, "is_const<const int>::value_type == bool");
            static_assert(is_same<is_const<const int>::type, true_type>::value, "is_const<const int>::type == true_type");
            Assert::IsTrue(is_const<const int>() == true, L"is_const<const int>() == true");

            static_assert(is_const<int>::value == false, "is_const<const int>::value == false");
            static_assert(is_same<is_const<int>::value_type, bool>::value, "is_const<int>::value_type == bool");
            static_assert(is_same<is_const<int>::type, false_type>::value, "is_const<int>::type == false_type");
            Assert::IsTrue(is_const<int>() == false, L"is_const<int>() == false");

            static_assert(is_const<const volatile int>::value == true, "is_const<const volatile int>::value == true");
            static_assert(is_const<const int&>::value == false, "is_const<const int&>::value == false");
            static_assert(is_const<const int*>::value == false, "is_const<const int*>::value == false");
            static_assert(is_const<int* const>::value == true, "is_const<int* const>::value == true");
        }

        TEST_METHOD(is_volatile_test)
        {
            using namespace nek;
            static_assert(is_volatile<volatile int>::value == true, "is_volatile<volatile int>::value == true");
            static_assert(is_same<is_volatile<volatile int>::value_type, bool>::value, "is_volatile<volatile int>::value_type == bool");
            static_assert(is_same<is_volatile<volatile int>::type, true_type>::value, "is_volatile<volatile int>::type == true_type");
            Assert::IsTrue(is_volatile<volatile int>() == true, L"is_volatile<volatile int>() == true");

            static_assert(is_volatile<int>::value == false, "is_volatile<int>::value == false");
            static_assert(is_same<is_volatile<int>::value_type, bool>::value, "is_volatile<int>::value_type == bool");
            static_assert(is_same<is_volatile<int>::type, false_type>::value, "is_volatile<int>::type == false_type");
            Assert::IsTrue(is_volatile<int>() == false, L"is_volatile<int>() == false");

            static_assert(is_volatile<const volatile int>::value == true, "is_volatile<const volatile int>::value == true");
            static_assert(is_volatile<volatile int&>::value == false, "is_volatile<volatile int&>::value == false");
            static_assert(is_volatile<volatile int*>::value == false, "is_volatile<volatile int*>::value == false");
            static_assert(is_volatile<int* volatile>::value == true, "is_volatile<int* volatile>::value == true");
        }

        TEST_METHOD(is_pointer_test)
        {
            using namespace nek;
            static_assert(is_pointer<int*>::value == true, "is_pointer<int*>::value == true");
            static_assert(is_same<is_pointer<int*>::type, true_type>::value, "is_pointer<int*>::type == true_type");
            static_assert(is_same<is_pointer<int*>::value_type, bool>::value, "is_same<is_pointer<int*>::value_type, bool>::value");
            Assert::IsTrue(is_pointer<int*>() == true, L"is_pointer<int*>() == true");
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
            static_assert(is_same<is_integral<int>::type, true_type>::value, "is_integral<int>::type == true_type");
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
            static_assert(is_same<is_void<void>::type, true_type>::value, "is_void<void>::type == true_type");
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
            static_assert(is_same<is_union<is_union_test_union>::type, true_type>::value, "is_union<is_union_test_union>::type == true_type");
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

        TEST_METHOD(is_enum_test)
        {
            using namespace nek;
            enum e {};
            enum class ec {};

            static_assert(is_enum<e>::value == true, "is_enum<e>::value == true");
            static_assert(is_same<is_enum<e>::value_type, bool>::value, "is_enum<e>::value_type == bool");
            static_assert(is_same<is_enum<e>::type, true_type>::value, "is_enum<e>::type == true_type");
            Assert::IsTrue(is_enum<e>() == true, L"is_enum<e>() == true");

            static_assert(is_enum<int>::value == false, "is_enum<int>::value == false");
            static_assert(is_same<is_enum<int>::value_type, bool>::value, "is_enum<int>::value_type == bool");
            static_assert(is_same<is_enum<int>::type, false_type>::value, "is_enum<int>::type == false_type");
            Assert::IsTrue(is_enum<int>() == false, L"is_enum<int>() == false");

            static_assert(is_enum<const e>::value == true, "is_enum<const e>::value == true");
            static_assert(is_enum<volatile e>::value == true, "is_enum<volatile e>::value == true");
            static_assert(is_enum<const volatile e>::value == true, "is_enum<const volatile e>::value == true");
            static_assert(is_enum<ec>::value == true, "is_enum<ec>::value == true");

            static_assert(is_enum<e*>::value == false, "is_enum<e*>::value == false");
            static_assert(is_enum<e&>::value == false, "is_enum<e&>::value == false");
            static_assert(is_enum<e()>::value == false, "is_enum<e()>::value == false");
            static_assert(is_enum<e[]>::value == false, "is_enum<e[]>::value == false");
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
            static_assert(is_same<is_class<is_class_test_class>::type, true_type>::value, "is_class<is_class_test_class>::type == true_type");
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

        TEST_METHOD(is_lvalue_reference_test)
        {
            using namespace nek;
            static_assert(is_lvalue_reference<int&>::value == true, "is_lvalue_reference<int&>::value == true");
            static_assert(is_same<is_lvalue_reference<int&>::type, true_type>::value, "is_lvalue_reference<int&>::type == true_type");
            static_assert(is_same<is_lvalue_reference<int&>::value_type, bool>::value, "is_lvalue_reference<int&>::value_type == bool");
            Assert::IsTrue(is_lvalue_reference<int&>() == true, L"is_lvalue_reference<int&>() == true");
            static_assert(is_lvalue_reference<int>::value == false, "is_lvalue_reference<int>::value == false");
            static_assert(is_lvalue_reference<int*&>::value == true, "is_lvalue_reference<int*&>::value == true");
            static_assert(is_lvalue_reference<int*>::value == false, "is_lvalue_reference<int*>::value == false");
            static_assert(is_lvalue_reference<const volatile int&>::value == true, "is_lvalue_reference<const volatile int&>::value == true");
            static_assert(is_lvalue_reference<int&&>::value == false, "is_lvalue_reference<int&&>::value == false");
            static_assert(is_lvalue_reference<void (&)()>::value == true, "is_lvalue_reference<void (&)()>::value == true");
            static_assert(is_lvalue_reference<int& ()>::value == false, "is_lvalue_reference<int& ()>::value == false");
            static_assert(is_lvalue_reference<int []>::value == false, "is_lvalue_reference<int []>::value == false");
        }

        TEST_METHOD(is_rvalue_reference_test)
        {
            using namespace nek;
            static_assert(is_rvalue_reference<int&&>::value == true, "is_rvalue_reference<int&&>::value == true");
            static_assert(is_same<is_rvalue_reference<int&&>::type, true_type>::value, "is_rvalue_reference<int&&>::type == true_type");
            static_assert(is_same<is_rvalue_reference<int&&>::value_type, bool>::value, "is_rvalue_reference<int&&>::value_type == bool");
            Assert::IsTrue(is_rvalue_reference<int&&>() == true, L"is_rvalue_reference<int&&>() == true");
            static_assert(is_rvalue_reference<int>::value == false, "is_rvalue_reference<int>::value == false");
            static_assert(is_rvalue_reference<int*&&>::value == true, "is_rvalue_reference<int*&&>::value == true");
            static_assert(is_rvalue_reference<int*>::value == false, "is_rvalue_reference<int*>::value == false");
            static_assert(is_rvalue_reference<const volatile int&&>::value == true, "is_rvalue_reference<const volatile int&&>::value == true");
            static_assert(is_rvalue_reference<int&>::value == false, "is_rvalue_reference<int&>::value == false");
            static_assert(is_rvalue_reference<void (&&)()>::value == true, "is_rvalue_reference<void (&&)()>::value == true");
            static_assert(is_rvalue_reference<int&& ()>::value == false, "is_rvalue_reference<int&& ()>::value == false");
            static_assert(is_rvalue_reference<int []>::value == false, "is_rvalue_reference<int []>::value == false");
        }

        TEST_METHOD(is_reference_test)
        {
            using namespace nek;
            static_assert(is_reference<int&>::value == true, "is_reference<int&>::value == true");
            static_assert(is_same<is_reference<int&>::type, true_type>::value, "is_reference<int&>::type == true_type");
            static_assert(is_same<is_reference<int&>::value_type, bool>::value, "is_reference<int&>::value_type == bool");
            Assert::IsTrue(is_reference<int&>() == true, L"is_reference<int&>() == true");
            static_assert(is_reference<int>::value == false, "is_reference<int>::value == false");
            static_assert(is_reference<int*&>::value == true, "is_reference<int*&>::value == true");
            static_assert(is_reference<int*>::value == false, "is_reference<int*>::value == false");
            static_assert(is_reference<const volatile int&>::value == true, "is_reference<const volatile int&>::value == true");
            static_assert(is_reference<int&&>::value == true, "is_reference<int&&>::value == true");
            static_assert(is_reference<void (&&)()>::value == true, "is_reference<void (&&)()>::value == true");
            static_assert(is_reference<int&& ()>::value == false, "is_reference<int&& ()>::value == false");
            static_assert(is_reference<int []>::value == false, "is_reference<int []>::value == false");
        }

        TEST_METHOD(is_floating_point_test)
        {
            using namespace nek;
            static_assert(is_floating_point<float>::value == true, "is_floating_point<float>::value == true");
            static_assert(is_same<is_floating_point<float>::type, true_type>::value, "is_floating_point<float>::type == true_type");
            static_assert(is_same<is_floating_point<float>::value_type, bool>::value, "is_floating_point<float>::value_type == bool");
            Assert::IsTrue(is_floating_point<float>() == true, L"is_floating_point<float>() == true");
            static_assert(is_floating_point<int>::value == false, "is_floating_point<int>::value == false");
            static_assert(is_floating_point<double>::value == true, "is_floating_point<double>::value == true");
            static_assert(is_floating_point<long double>::value == true, "is_floating_point<long double>::value == true");
            static_assert(is_floating_point<const volatile float>::value == true, "is_floating_point<const volatile float>::value == true");
            static_assert(is_floating_point<unsigned>::value == false, "is_floating_point<unsigned>::value == false");
            static_assert(is_floating_point<float*>::value == false, "is_floating_point<float*>::value == false");
            static_assert(is_floating_point<double&>::value == false, "is_floating_point<double&>::value == false");
            static_assert(is_floating_point<long double[1]>::value == false, "is_floating_point<long double[1]>::value == false");
            static_assert(is_floating_point<double ()>::value == false, "is_floating_point<double ()>::value == false");
        }

        TEST_METHOD(make_unsigned_test)
        {
            using namespace nek;
            enum E1 {AA, BB, CC};
            enum class E2 : char {AA, BB, CC};
            static_assert(is_same<make_unsigned<int>::type, unsigned int>::value, "make_unsigned<int> == unsigned int");
            static_assert(is_same<make_unsigned<unsigned char>::type, unsigned char>::value, "make_unsigned<unsigned char> == unsigned char");
            static_assert(is_same<make_unsigned<const short>::type, const unsigned short>::value, " make_unsigned<const short> == const unsinged short");
            static_assert(is_same<make_unsigned<const volatile unsigned long>::type, const volatile unsigned long>::value, "make_unsigned<const volatile long> == const volatile unsigned long");
            static_assert(is_same<make_unsigned<E1>::type, unsigned int>::value, "make_unsigned<enum> == unsigned int");
            static_assert(is_same<make_unsigned<E2>::type, unsigned char>::value, "make_unsigned<enum class : char> == unsigned char");
        }
    };
}