#include <nek/utility/move_if_noexcept.hpp>
#include <gtest/gtest.h>
#include <string>

namespace
{
    struct noexceptable
    {
        std::string log = "";

        noexceptable() = default;

        noexceptable(noexceptable const&) noexcept
        {
            log += "copy ctor";
        }

            noexceptable(noexceptable&&) noexcept
        {
            log += "move ctor";
        }
    };

    struct exceptable
    {
        std::string log = "";

        exceptable() = default;

        exceptable(exceptable const&)
        {
            log += "copy ctor";
        }

        exceptable(exceptable&&)
        {
            log += "move ctor";
        }
    };
}

TEST(move_if_noexcept_test, except)
{
    exceptable e;
    auto actual = nek::move_if_noexcept(e);
    EXPECT_EQ("copy ctor", actual.log);
}

TEST(move_if_noexcept_test, noexcept)
{
    noexceptable e;
    auto actual = nek::move_if_noexcept(e);
    EXPECT_EQ("move ctor", actual.log);
}
