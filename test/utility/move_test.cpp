#include <string>
#include <nek/utility/move.hpp>
#include <gtest/gtest.h>

namespace
{
    struct move_logging_mock
    {
        std::string log = "";

        move_logging_mock() = default;

        move_logging_mock(move_logging_mock const&)
        {
            log += "copy";
        }

        move_logging_mock(move_logging_mock&&)
        {
            log += "move";
        }
    };
}

TEST(move_test, call_move_constructor)
{
    move_logging_mock m;
    move_logging_mock m2 = m;
    EXPECT_EQ("copy", m2.log);

    move_logging_mock m3 = nek::move(m);
    EXPECT_EQ("move", m3.log);
}
