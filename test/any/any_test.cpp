#include <nek/any.hpp>
#include <gtest/gtest.h>

namespace
{
    class dummy
    {
    };
}

TEST(any_test, default_constructor)
{
    nek::any instance;

    // verify
    EXPECT_TRUE(instance.is_empty());
    EXPECT_EQ(typeid(void), instance.type());
}

TEST(any_test, convert_construct)
{
    int expected = 1;
    nek::any instance = expected;

    // verify
    EXPECT_FALSE(instance.is_empty());
    EXPECT_EQ(typeid(int), instance.type());

    EXPECT_EQ(nullptr, nek::any_cast<dummy>(&instance));
    ASSERT_NE(nullptr, nek::any_cast<int>(&instance));

    // values should be equal, but addresses should not be equal
    EXPECT_EQ(expected, *(nek::any_cast<int>(&instance)));
    EXPECT_NE(&expected, nek::any_cast<int>(&instance));
}

TEST(any_test, copy_constructor)
{
    int expected = 1;
    nek::any original = expected;
    nek::any instance = original;

    // verify
    EXPECT_FALSE(instance.is_empty());
    EXPECT_EQ(original.type(), instance.type());

    EXPECT_EQ(nullptr, nek::any_cast<dummy>(&instance));
    ASSERT_NE(nullptr, nek::any_cast<int>(&instance));

    // values should be equal, but addresses should not be equal
    EXPECT_EQ(nek::any_cast<int>(original), nek::any_cast<int>(instance));
    EXPECT_NE(nek::any_cast<int>(&original), nek::any_cast<int>(&instance));
}

TEST(any_test, copy_assign)
{
    int expected = 1;
    nek::any original = expected;
    nek::any sut;

    // exercise
    sut = original;

    EXPECT_FALSE(sut.is_empty());
    EXPECT_EQ(typeid(int), sut.type());

    EXPECT_EQ(nullptr, nek::any_cast<dummy>(&sut));
    EXPECT_NE(nullptr, nek::any_cast<int>(&sut));

    EXPECT_EQ(expected, nek::any_cast<int>(sut));
    EXPECT_NE(&expected, nek::any_cast<int>(&sut));

    EXPECT_EQ(nek::any_cast<int>(original), nek::any_cast<int>(sut));
    EXPECT_NE(nek::any_cast<int>(&original), nek::any_cast<int>(&sut));
}

TEST(any_test, convert_assign)
{
    int expected = 1;
    nek::any sut;

    // exercise
    sut = expected;

    EXPECT_FALSE(sut.is_empty());
    EXPECT_EQ(typeid(int), sut.type());

    EXPECT_EQ(nullptr, nek::any_cast<dummy>(&sut));
    EXPECT_NE(nullptr, nek::any_cast<int>(&sut));

    EXPECT_EQ(expected, nek::any_cast<int>(sut));
    EXPECT_NE(&expected, nek::any_cast<int>(&sut));
}

TEST(any_test, swap)
{
    int value = 1;
    nek::any original = value;
    nek::any swapped;

    // exercise
    original.swap(swapped);

    EXPECT_TRUE(original.is_empty());
    EXPECT_EQ(typeid(void), original.type());

    EXPECT_FALSE(swapped.is_empty());
    EXPECT_EQ(typeid(int), swapped.type());

    EXPECT_EQ(value, nek::any_cast<int>(swapped));
    EXPECT_NE(&value, nek::any_cast<int>(&swapped));
}

TEST(any_test, non_member_swap)
{
    int value = 1;
    nek::any original = value;
    nek::any swapped;

    // exercise
    nek::swap(original, swapped);

    EXPECT_TRUE(original.is_empty());
    EXPECT_EQ(typeid(void), original.type());

    EXPECT_FALSE(swapped.is_empty());
    EXPECT_EQ(typeid(int), swapped.type());

    EXPECT_EQ(value, nek::any_cast<int>(swapped));
    EXPECT_NE(&value, nek::any_cast<int>(&swapped));
}

TEST(any_test, clear)
{
    nek::any sut = 1;

    EXPECT_FALSE(sut.is_empty());
    nek::clear(sut);
    EXPECT_TRUE(sut.is_empty());
    nek::clear(sut);
    EXPECT_TRUE(sut.is_empty());
    sut = 1;
    EXPECT_FALSE(sut.is_empty());
    nek::clear(sut);
    EXPECT_TRUE(sut.is_empty());
}

TEST(any_test, const_any_cast)
{
    nek::any const sut = 1;
    int value = nek::any_cast<int>(sut);
    EXPECT_EQ(1, value);
    int const* pointer = nek::any_cast<int>(&sut);
    EXPECT_EQ(1, *pointer);
}

TEST(any_test, bad_cast)
{
    int stub = 0;
    nek::any sut = stub;
    EXPECT_THROW(nek::any_cast<dummy>(sut);, nek::bad_any_cast_exception);
    nek::bad_any_cast_exception e;
    EXPECT_NE(nullptr, e.what());
}