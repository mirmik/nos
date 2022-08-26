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

TEST_CASE("logging level")
{
    nos::stringstream ss;
    nos::current_ostream = &ss;
    auto logger = nos::log::logger("logger").set_level(nos::log::level::Info);
    logger.log(nos::log::level::Debug, "Hello, world!");
    CHECK_EQ(ss.str(), "");
    logger.set_level(nos::log::level::Debug);
    logger.log(nos::log::level::Debug, "Hello, world!");
    CHECK_EQ(ss.str(), "[debug] Hello, world!\n");
}