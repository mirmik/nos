#include <cmath>
#include <doctest/doctest.h>
#include <nos/shell/comfortable_function.h>

TEST_CASE("kwargs")
{
    nos::comfortable_function<int(int, int)> func(
        [](int a, int b) { return std::pow(a, b); }, {"a", "b"});

    nos::comfortable_function<int(nos::trent)> bar(
        [](nos::trent a) { return a[0].as_numer() * a[1].as_numer(); }, {"a"});

    CHECK_EQ(func(2, 3), 8);
    CHECK_EQ(func(nos::argpair("a", 2), 3), 8);
    CHECK_EQ(func(2, nos::argpair("b", 3)), 8);
    CHECK_EQ(func(nos::argpair("a", 2), nos::argpair("b", 3)), 8);
    CHECK_EQ(func(nos::argpair("b", 3), nos::argpair("a", 2)), 8);

    CHECK_EQ(func("2", 3), 8);
    CHECK_EQ(func(nos::argpair("a", "2"), 3), 8);
    CHECK_EQ(func("2", nos::argpair("b", 3)), 8);
    CHECK_EQ(func(nos::argpair("b", "3"), nos::argpair("a", 2)), 8);

    nos::trent t;
    t.push_back(2);
    t.push_back("3");
    CHECK_EQ(bar(t), 6);
}
