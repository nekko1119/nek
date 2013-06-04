#include "stdafx.h"
#include "CppUnitTest.h"
#include <nek/utility/move.hpp>
#include <nek/utility/swap.hpp>
#include <nek/utility/addressof.hpp>
#include <nek/utility/forward.hpp>
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
    };
}