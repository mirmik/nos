#include <doctest/doctest.h>
#include <nos/shell/comfortable_function.h>

TEST_CASE("kwargs")
{
    nos::comfortable_function<int(int, int)> func(
        [](int a, int b) { return a + b; }, {"a", "b"});

    CHECK_EQ(func(1, 2), 3);
    CHECK_EQ(func(nos::arg("a", 1), 2), 3);
    CHECK_EQ(func(1, nos::arg("a", 2)), 3);
    CHECK_EQ(func(nos::arg("a", 1), nos::arg("b", 2)), 3);

    CHECK_EQ(func("1", 2), 3);
    CHECK_EQ(func(nos::arg("a", "1"), 2), 3);
    CHECK_EQ(func("1", nos::arg("a", 2)), 3);
    CHECK_EQ(func(nos::arg("a", "1"), nos::arg("b", 2)), 3);
}
