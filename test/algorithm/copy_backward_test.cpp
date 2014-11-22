#include <algorithm>
#include <nek/algorithm/copy_backward.hpp>
#include <gtest/gtest.h>

TEST(copy_backward_test, raw_array)
{
    // setup
    int src[4] = {1, 2, 3, 4};
    int dest[4] = {};

    // exercise
    nek::copy_backward(src, src + 4, dest + 4);

    // verify
    EXPECT_EQ(1, dest[0]);
    EXPECT_EQ(2, dest[1]);
    EXPECT_EQ(3, dest[2]);
    EXPECT_EQ(4, dest[3]);
}

TEST(copy_backward_test, dynamic_array)
{
    // setup
    int* src = new int[4];
    src[0] = 1;
    src[1] = 2;
    src[2] = 3;
    src[3] = 4;
    int* dest = new int[4]{};

    // exercise
    nek::copy_backward(src, src + 4, dest + 4);

    // verify
    EXPECT_EQ(1, dest[0]);
    EXPECT_EQ(2, dest[1]);
    EXPECT_EQ(3, dest[2]);
    EXPECT_EQ(4, dest[3]);

    // tear down
    delete[] src;
    delete[] dest;
}

TEST(copy_backward_test, backward)
{
    int a[] = {0, 1, 2, 3};
    int expected[] = {0, 0, 1, 2};
    nek::copy_backward(a, a + 3, a + 4);
    EXPECT_TRUE(std::equal(a, a + 4, expected));
}
