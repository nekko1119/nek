#include <nek/uninitialized/uninitialized_copy.hpp>
#include <gtest/gtest.h>
#include <vector>

TEST(uninitialized_copy_test, normal)
{
    std::vector<int> v = {1, 2, 3};
    std::allocator<int> alloc;
    constexpr std::size_t size = 3;
    auto buf = alloc.allocate(3);

    nek::uninitialized_copy(v.begin(), v.end(), buf);

    EXPECT_EQ(1, buf[0]);
    EXPECT_EQ(2, buf[1]);
    EXPECT_EQ(3, buf[2]);

    for (int i = 0; i < size; ++i) {
        alloc.destroy(buf + i);
    }

    alloc.deallocate(buf, size);
}

TEST(uninitialized_copy_n_test, normal)
{
    std::vector<int> v = {1, 2, 3};
    std::allocator<int> alloc;
    constexpr std::size_t size = 3;
    auto buf = alloc.allocate(3);

    nek::uninitialized_copy_n(v.begin(), size, buf);
    EXPECT_EQ(1, buf[0]);
    EXPECT_EQ(2, buf[1]);
    EXPECT_EQ(3, buf[2]);

    for (int i = 0; i < size; ++i) {
        alloc.destroy(buf + i);
    }

    alloc.deallocate(buf, size);
}