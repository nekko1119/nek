#include "stdafx.h"
#include "CppUnitTest.h"
#include <nek/allocator/allocator.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace nektest
{
    TEST_CLASS(allocator_test)
    {
    public:

        class allocator_test_class
        {
        public:
            allocator_test_class(int i, double d)
                : a(i), b(d)
            {
                Logger::WriteMessage(L"constructor\n");
            }

            allocator_test_class& operator=(const allocator_test_class& right)
            {
                Logger::WriteMessage(L"operator=\n");
                a = right.a;
                b = right.b;
                return *this;
            }

            ~allocator_test_class()
            {
                Logger::WriteMessage(L"destructor\n");
            }

            int a;
            double b;
        };

        template <class T>
        struct type_holder
        {
            typedef T type;
        };

        TEST_METHOD(default_allocator_test)
        {
            using namespace nek;
            allocator<allocator_test_class> alloc_test;
            allocator_test_class* arr = alloc_test.allocate(10);
            Assert::ExpectException<std::bad_alloc>([&alloc_test]()
            {
                alloc_test.allocate(alloc_test.max_size() + 1);
            }, L"throw std::bad_alloc");
            Assert::ExpectException<std::bad_alloc>([&alloc_test]()
            {
                alloc_test.allocate(0);
            }, L"throw std::bad_alloc");
            arr[9] = allocator_test_class(1, 1.0);
            Assert::AreEqual(1, arr[9].a, L"arr[9].a == 1");
            alloc_test.construct(&arr[3], 2, 2.0);
            Assert::AreEqual(2.0, arr[3].b, L"arr[3].b == 2.0");
            int a;
            type_holder<decltype(alloc_test)>::type::template rebind<int>::other alloc_int;
            Assert::AreEqual(&a, alloc_int.address(a), L"&a == address(a)");
            Assert::AreEqual(static_cast<std::size_t>(-1) / sizeof(allocator_test_class), alloc_test.max_size(), L"max_size");
            alloc_test.destroy(arr);
            Logger::WriteMessage(L"destroyed\n");
            alloc_test.deallocate(arr, 0U);
            Logger::WriteMessage(L"deallocated\n");
            Assert::IsTrue(alloc_test == alloc_int, L"alloc_test == alloc_int");
        }
    };
}