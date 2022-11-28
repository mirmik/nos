#include <cmath>
#include <doctest/doctest.h>
#include <nos/shell/weaked_function.h>

class TestComfortableFunction
{
public:
    int a = 0;
    int b = 0;

    TestComfortableFunction() = default;
    TestComfortableFunction(int a, int b) : a(a), b(b) {}

public:
    int sum(int c)
    {
        return a + b + c;
    }
};

int sum(int a, int b)
{
    return a + b;
}

TEST_CASE("kwargs")
{
    nos::weaked_function<int(int, int)> func(
        [](int a, int b) { return std::pow(a, b); }, {"a", "b"});

    nos::weaked_function<int(nos::trent)> bar(
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

    TestComfortableFunction tcf(1, 2);
    nos::weaked_function<int(int)> test_func(
        [&tcf](int c) { return tcf.sum(c); }, {"c"});

    CHECK_EQ(test_func(3), 6);
}

TEST_CASE("make_cf_abstract")
{
    nos::wf_collection collection;
    collection.add("sum", std::function<int(int, int)>(sum));
    collection.add(
        "sub",
        std::function<int(int, int)>([](int a, int b) { return a - b; }));
    collection.add("pow",
                   std::function<int(int, int)>([](int a, int b)
                                                { return std::pow(a, b); }),
                   {"a", "b"});
    collection.add(
        "stub", std::function<void(int, int)>([](int, int) {}), {"a", "b"});

    CHECK_EQ(
        collection
            .execute("sum", {nos::trent_argument{3}, nos::trent_argument{7}})
            .as_numer(),
        10);
    CHECK_EQ(
        collection
            .execute("sub", {nos::trent_argument{3}, nos::trent_argument{7}})
            .as_numer(),
        -4);
    CHECK_EQ(
        collection
            .execute("pow",
                     {nos::trent_argument{7, "b"}, nos::trent_argument{3, "a"}})
            .as_numer(),
        2187);

    TestComfortableFunction tcf(2, 3);
    collection.add(
        "tcf", std::function<int(int)>([&tcf](int c) { return tcf.sum(c); }));
    CHECK_EQ(collection.execute("tcf", {nos::trent_argument{4}}).as_numer(), 9);
}