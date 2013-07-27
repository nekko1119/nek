#include "stdafx.h"
#include "CppUnitTest.h"
#include <nek/any.hpp>
#include <nek/type_traits/is_same.hpp>
#include <string>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft { namespace VisualStudio { namespace CppUnitTestFramework {
    template<>
    static std::wstring ToString<std::type_info>(const std::type_info& t)
    {
        RETURN_WIDE_STRING(t.name());
    }

    template<>
    static std::wstring ToString<std::string>(std::string* t)
    {
        RETURN_WIDE_STRING(t->c_str());
    }

    template<>
    static std::wstring ToString<nek::any>(nek::any* t)
    {
        RETURN_WIDE_STRING(typeid(t).name());
    }
}}}

namespace nektest
{
    TEST_CLASS(any_test)
    {
    public:

        TEST_METHOD(default_ctor_test)
        {
            using namespace nek;
            const any a;
            Assert::IsTrue(a.empty(), L"empty");
            Assert::AreEqual(typeid(void), a.type(), L"type");
            Assert::IsNull(any_cast<int>(&a), L"any_cast<int>");
        }

        TEST_METHOD(converting_ctor_test)
        {
            using namespace nek;
            std::string text("test");
            any a(text);
            Assert::IsFalse(a.empty(), L"empty");
            Assert::AreEqual(typeid(std::string), a.type(), L"type");
            Assert::IsNull(any_cast<int>(&a), L"any_cast<int>");
            Assert::IsNotNull(any_cast<std::string>(&a), L"any_cast<std::string>");
            Assert::AreEqual(text, any_cast<std::string>(a), L"text == any");
            Assert::AreNotEqual(&text, any_cast<std::string>(&a), L"&text != &any");
        }

        TEST_METHOD(copy_ctor_test)
        {
            using namespace nek;
            std::string text("test");
            any original(text);
            any copy(original);
            Assert::IsFalse(copy.empty(), L"empty");
            Assert::AreEqual(original.type(), copy.type(), L"type");
            Assert::AreEqual(any_cast<std::string>(original), any_cast<std::string>(copy), L"casted original == casted copy");
            Assert::AreEqual(text, any_cast<std::string>(copy), L"text == casted copy");
            Assert::AreNotEqual(&text, any_cast<std::string>(&copy), L"&text != casted &copy");
        }

        TEST_METHOD(copy_assign_test)
        {
            using namespace nek;
            std::string text("test");
            any original(text);
            any copy;
            copy = original;
            Assert::IsFalse(copy.empty(), L"empty");
            Assert::AreEqual(original.type(), copy.type(), L"type");
            Assert::AreEqual(any_cast<std::string>(original), any_cast<std::string>(copy), L"casted original == casted copy");
            Assert::AreEqual(text, any_cast<std::string>(copy), L"text == casted copy");
            Assert::AreNotEqual(any_cast<std::string>(&original), any_cast<std::string>(&copy), L"casted &original == casted &copy");
        }

        TEST_METHOD(converting_assign_test)
        {
            using namespace nek;
            std::string text("test");
            any assign;
            assign = text;
            Assert::IsFalse(assign.empty(), L"empty");
            Assert::AreEqual(typeid(std::string), assign.type(), L"type");
            Assert::IsNull(any_cast<int>(&assign), L"any_cast<int>");
            Assert::IsNotNull(any_cast<std::string>(&assign), L"any_cast<std::string>");
            Assert::AreEqual(text, any_cast<std::string>(assign), L"text == casted assign");
            Assert::AreNotEqual(&text, any_cast<std::string>(&assign), L"&text == casted &assign");
        }

        TEST_METHOD(bad_cast_test)
        {
            using namespace nek;
            std::string text("test");
            any value = text;

            Assert::ExpectException<bad_any_cast_exception>([&value](){any_cast<const char*>(value);}, L"any_cast throw bad_any_cast");
        }

        TEST_METHOD(swap_test)
        {
            using namespace nek;
            std::string text("test");
            any original = text;
            any swapped;
            std::string* original_ptr = any_cast<std::string>(&original);
            any* swap_result = &original.swap(swapped);
            Assert::IsTrue(original.empty(), L"empty on original");
            Assert::IsFalse(swapped.empty(), L"empty on swapped");
            Assert::AreEqual(typeid(std::string), swapped.type(), L"type");
            Assert::AreEqual(text, any_cast<std::string>(swapped), L"text == casted swapped");
            Assert::IsNotNull(original_ptr, L"original_ptr");
            Assert::AreEqual(original_ptr, any_cast<std::string>(&swapped), L"original_ptr == casted &swapped");
            Assert::AreEqual(swap_result, &original, L"swap_result == &original");
        }

        TEST_METHOD(null_copying_test)
        {
            using namespace nek;
            const any null;
            any copied = null;
            any assigned;
            assigned = null;

            Assert::IsTrue(null.empty(), L"empty on null");
            Assert::IsTrue(copied.empty(), L"empty on copied");
            Assert::IsTrue(assigned.empty(), L"empty on assigned");
        }

        TEST_METHOD(cast_to_reference_test)
        {
            using namespace nek;
            any a(10);
            const any b(a);
            int& ra = any_cast<int&>(a);
            const int& cra = any_cast<const int&>(a);
            volatile int& vra = any_cast<volatile int&>(a);
            const volatile int& cvra = any_cast<const volatile int&>(a);
            Assert::IsTrue(&ra == &cra && &ra == &vra && &ra == &cvra, L"cv reference");

            const int& crb = any_cast<const int&>(b);
            const volatile int& cvrb = any_cast<const volatile int&>(b);

            Assert::IsTrue(&crb == &cvrb, L"&crb == &cvrb");
            Assert::IsTrue(&ra != &crb, L"&ra != &crb");

            ++ra;
            int incremented = any_cast<int>(a);
            Assert::AreEqual(11, incremented, L"incremented == 11");
            Assert::ExpectException<bad_any_cast_exception>([&a]()
            {
                any_cast<char&>(a);
            }, L"any_cast to incorrect reference type");
        }

        TEST_METHOD(is_any_test)
        {
            using namespace nek;
            static_assert(is_any<any>::value == true, "is_any<any>::value == true");
            static_assert(is_same<is_any<any>::type, true_type>::value, "is_any<any>::type == true_type");
            static_assert(is_same<is_any<any>::value_type, bool>::value, "is_any<any>::value_type == bool");
            Assert::IsTrue(is_any<any>() == true, L"is_any<any>() ==true");
            static_assert(is_any<int>::value == false, "is_any<int>::value == false");
            static_assert(is_any<any*>::value == false, "is_any<any*>::value == false");
            static_assert(is_any<const volatile any>::value == true, "is_any<const volatile any>::value == true");
        }
    };
}