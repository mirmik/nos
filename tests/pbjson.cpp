#include <doctest/doctest.h>
#include <nos/trent/pbjson.h>

TEST_CASE("pbjson_test_get_type")
{
    std::string data;
    data.resize(2);
    data[0] = 0x21;
    data[1] = 0x0A;
    nos::pbjson::parser parser({(char *)data.data(), data.size()});
    CHECK_EQ(parser.buf[0], 0x21);
    CHECK_EQ(parser.buf[1], 0x0A);
    auto [type, len] = parser.get_type_and_length();
    CHECK_EQ(type, 2);
    CHECK_EQ(len, 1);
}

TEST_CASE("pbjson_test_int")
{
    std::string data("\x21\x0A");
    nos::pbjson::parser parser({(char *)data.data(), data.size()});
    nos::trent tr = parser.parse();
    CHECK_EQ(tr.as_numer(), 10);
}

TEST_CASE("pbjson_test_string")
{
    std::string data("\x85hello");
    nos::pbjson::parser parser({(char *)data.data(), data.size()});
    nos::trent tr = parser.parse();
    CHECK_EQ(tr.as_string(), "hello");
}

TEST_CASE("pbjson_test_dict")
{
    std::string data("\xE1\x05hello\x85world");
    nos::pbjson::parser parser({(char *)data.data(), data.size()});
    nos::trent tr = parser.parse();
    CHECK_EQ(tr["hello"].as_string(), "world");
}