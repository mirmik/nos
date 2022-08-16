#include <doctest/doctest.h>
#include <nos/input.h>
#include <nos/io/sstream.h>

TEST_CASE("read_from")
{
    nos::stringstream ss("Hello World!");
    CHECK(nos::read_from(ss, 5) == "Hello");
    CHECK(nos::read_from(ss, 6) == " World");
    CHECK(nos::read_from(ss, 5) == "!");
}