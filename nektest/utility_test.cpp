#include "stdafx.h"
#include "CppUnitTest.h"
#include <memory>
#include <nek/utility/move.hpp>
#include <nek/utility/swap.hpp>
#include <nek/utility/addressof.hpp>
#include <nek/utility/forward.hpp>
#include <nek/utility/pointer_traits.hpp>
#include <nek/type_traits/integral_constant.hpp>
#include <nek/type_traits/is_same.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nektest
{		
    TEST_CLASS(utility_test)
    {
    public:

        struct move_test_class
        {
            move_test_class(){}
            move_test_class(const move_test_class&)
            {
                Logger::WriteMessage("copy\n");
            }
            move_test_class(move_test_class&&)
            {
                Logger::WriteMessage("move\n");
            }
        };

        TEST_METHOD(move_test)
        {
            using namespace nek;
            move_test_class m;
            move_test_class n = m;
            move_test_class o = move(m);
        }

        TEST_METHOD(swap_test)
        {
            using namespace nek;
            int a = 10, b = 20;
            swap(a, b);
            Assert::IsTrue(a == 20 && b == 10, L"int swap");
            const wchar_t* aaa = L"aaa";
            const wchar_t* bbb = L"bbb";
            swap(aaa, bbb);
            Assert::AreEqual(aaa, L"bbb", L"aaa == \"bbb\"");
            Assert::AreEqual(bbb, L"aaa", L"bbb == \"aaa\"");
            int x[] = {1, 2, 3};
            int y[] = {10, 20, 30};
            swap(x, y);
            for(int i = 0; i < 3; ++i)
            {
                Assert::AreEqual(x[i], (i + 1) * 10, L"x == {10, 20, 30}");
            }
            for(int i = 0; i < 3; ++i)
            {
                Assert::AreEqual(y[i], i + 1, L"y == {1, 2, 3}");
            }
        }

        struct addressof_test_class
        {
            void* operator&()
            {
                return nullptr;
            }
        };

        TEST_METHOD(addressof_test)
        {
            using namespace nek;
            int i = 0;
            Assert::AreEqual(&i, addressof(i), L"&i == addressof(i)");

            addressof_test_class a;
            Assert::IsNotNull(addressof(a), L"addressof a is not null pointer");
            Assert::IsNull(&a, L"&a is null pointer");
        }

        void forward_test_func_i(int&&)
        {
            Logger::WriteMessage(L"int&&\n");
        }
        void forward_test_func_i(const int&)
        {
            Logger::WriteMessage(L"const int&\n");
        }
        template <class T>
        void forward_test_func(T&& value)
        {
            forward_test_func_i(nek::forward<T>(value));
        }

        TEST_METHOD(forward_test)
        {
            using namespace nek;
            int a = 0;
            forward_test_func(move(a));
            forward_test_func(a);
        }

        TEST_METHOD(pointer_traits1_test)
        {
            using namespace nek;
            typedef pointer_traits<std::shared_ptr<int>> shared;
            static_assert(is_same<shared::pointer, std::shared_ptr<int>>::value, "pointer_traits<shared_ptr<int>>::pointer == shared_ptr<int>");
            static_assert(is_same<shared::element_type, int>::value, "pointer_traits<shared_ptr<int>>::element_type == int");
            static_assert(is_same<shared::difference_type, std::ptrdiff_t>::value, "pointer_traits<shared_ptr<int>>::difference_type == ptrdiff_t");
            typedef shared::rebind<double>::other another;
            static_assert(is_same<another, std::shared_ptr<double>>::value, "pointer_traits<shared_ptr<int>::rebind<double>::other == shared_ptr<double>");
            //this expression is compile error. it is right action. [20.6.3.2]
            //int a;
            //Assert::AreEqual(&a, shared::pointer_to(a).get(), L"&a == pointer_traits<shared_ptr<int>>::pointer_to(a)");
            typedef pointer_traits<std::shared_ptr<void>> shared_void;
            static_assert(is_same<shared_void::pointer, std::shared_ptr<void>> ::value, "pointer_traits<shared_ptr<void>>::pointer == shared_ptr<void>");
            static_assert(is_same<shared_void::element_type, void>::value, "pointer_traits<shared_ptr<void>>::element_type == void");
            static_assert(is_same<shared_void::difference_type, std::ptrdiff_t>::value, "pointer_traits<shared_ptr<void>>::difference_type == ptrdiff_t");
            typedef shared::rebind<double>::other another;
            static_assert(is_same<another, std::shared_ptr<double>>::value, "pointer_traits<shared_ptr<void>::rebind<double>::other == shared_ptr<double>");
        }

        TEST_METHOD(pointer_traits2_test)
        {
            using namespace nek;
            typedef pointer_traits<int*> int_ptr;
            static_assert(is_same<int_ptr::pointer, int*>::value, "pointer_traits<int*>::pointer == int*");
            static_assert(is_same<int_ptr::element_type, int>::value, "pointer_traits<int*>::element_type == int");
            static_assert(is_same<int_ptr::difference_type, std::ptrdiff_t>::value, "pointer_traits<int*>::difference_type == ptrdiff_t");
            static_assert(is_same<int_ptr::rebind<double>::other, double*>::value, "pointer_traits<int>::rebind<double>::other == double*");
            int a;
            Assert::AreEqual(&a, int_ptr::pointer_to(a), L"&a == pointer_traits<int>::pointer_to(a)");
            typedef pointer_traits<void*> void_ptr;
            static_assert(is_same<void_ptr::pointer, void*>::value, "pointer_traits<void*>::pointer == void*");
            static_assert(is_same<void_ptr::element_type, void>::value, "pointer_traits<void*>::element_type == void");
            static_assert(is_same<void_ptr::difference_type, std::ptrdiff_t>::value, "pointer_traits<void*>::difference_type == ptrdiff_t");
            static_assert(is_same<void_ptr::rebind<double>::other, double*>::value, "pointer_traits<void>::rebind<double>::other == double*");

            //if element_type is void, type of `value` is unspecified. [20.6.3.2]
            //int b;
            //Assert::AreEqual(&b, int_ptr::pointer_to(b), L"&a == pointer_traits<void>::pointer_to(a)");
        }
    };
}