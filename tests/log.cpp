#include <doctest/doctest.h>
#include <nos/io/sstream.h>
#include <nos/log.h>

TEST_CASE("nos.log")
{
    nos::stringstream ss;
    nos::current_ostream = &ss;
    nos::log::info("Hello, world!");
    CHECK_EQ(ss.str(), "[ info] Hello, world!\n");
    nos::current_ostream = nullptr;
}