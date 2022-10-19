#include <cmath>
#include <doctest/doctest.h>
#include <nos/io/sstream.h>
#include <nos/print.h>

TEST_CASE("ibin")
{
    nos::stringstream ss;

    SUBCASE("u8")
    {
        uint8_t u8 = 0b10101010;
        nos::print_to(ss, nos::ibin(u8));
        CHECK_EQ(ss.str(), "0b10101010");
    }

    SUBCASE("u16")
    {
        uint16_t u16 = 0b1010101010101010;
        nos::print_to(ss, nos::ibin(u16));
        CHECK_EQ(ss.str(), "0b1010101010101010");
    }
}

TEST_CASE("ihex")
{
    nos::stringstream ss;

    SUBCASE("u8")
    {
        uint8_t u8 = 0b10101010;
        nos::print_to(ss, nos::ihex(u8));
        CHECK_EQ(ss.str(), "0xAA");
    }

    SUBCASE("u16")
    {
        uint16_t u16 = 0b1010101010101010;
        nos::print_to(ss, nos::ihex(u16));
        CHECK_EQ(ss.str(), "0xAAAA");
    }
}