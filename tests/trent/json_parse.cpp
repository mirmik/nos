#include <doctest/doctest.h>
#include <nos/trent/json.h>

TEST_CASE("json parses numeric scalars with whitespace and comments")
{
    nos::trent tr;

    tr = nos::json::parse("13");
    CHECK_EQ(tr.as_numer(), 13);

    tr = nos::json::parse("0.5");
    CHECK_EQ(tr.as_numer(), 0.5);

    tr = nos::json::parse("-0.5");
    CHECK_EQ(tr.as_numer(), -0.5);

    tr = nos::json::parse("/*13*/ 42");
    CHECK_EQ(tr.as_numer(), 42);

    tr = nos::json::parse(" 20e-1 ");
    CHECK_EQ(tr.as_numer(), doctest::Approx(2.0));
}

TEST_CASE("json parses arrays and dicts through comments and newlines")
{
    auto dict = nos::json::parse("{'a':42, /*aaa*/ 'b' : 13}");
    CHECK(dict.is_dict());

    dict = nos::json::parse("{'a':42, /*aaa*/ 'b' : 13 }");
    CHECK(dict.is_dict());

    auto list = nos::json::parse(R"(
        [42, //aaa
        13]
    )");
    CHECK(list.is_list());

    list = nos::json::parse(R"(

        [42,

    /*aaa*/

    13]

    )");
    CHECK(list.is_list());
}

TEST_CASE("json parses empty objects inside arrays")
{
    auto tr = nos::json::parse(R"(
        {
            "items": [
                {},
                {"k": 1}
            ]
        }
    )");

    CHECK(tr.is_dict());
    CHECK(tr["items"].is_list());
    CHECK_EQ(tr["items"].as_list().size(), 2);
    CHECK(tr["items"][0].is_dict());
    CHECK(tr["items"][0].as_dict().empty());
    CHECK_EQ(tr["items"][1]["k"].as_numer(), 1);
}

TEST_CASE("json parses booleans and nil/null mnemonics")
{
    auto tr = nos::json::parse(" {'a': false} ");
    CHECK(tr["a"].is_bool());
    CHECK_FALSE(tr["a"].as_bool());

    tr = nos::json::parse(" {'a': false } ");
    CHECK(tr["a"].is_bool());
    CHECK_FALSE(tr["a"].as_bool());

    tr = nos::json::parse("nil");
    CHECK(tr.is_nil());

    tr = nos::json::parse("{'a': nil}");
    CHECK(tr["a"].is_nil());

    tr = nos::json::parse("null");
    CHECK(tr.is_nil());

    tr = nos::json::parse("{'a': null}");
    CHECK(tr["a"].is_nil());
}
