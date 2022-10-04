#include <cmath>
#include <doctest/doctest.h>
#include <nos/trent/json.h>
#include <nos/trent/json_print.h>

TEST_CASE("json_test.to_string")
{
    nos::trent tr;
    tr["a"].as_list();
    tr["b"].as_list();

    for (int i = 0; i < 3; i++)
    {
        tr["a"].as_list().push_back(i);
        tr["b"].as_list().push_back(i);
    }

    auto str = nos::json::to_string(tr);

    CHECK_EQ(str, R"({"a":[0,1,2],"b":[0,1,2]})");
}