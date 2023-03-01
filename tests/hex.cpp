#include <doctest/doctest.h>
#include <nos/io/sstream.h>
#include <nos/print.h>

TEST_CASE("printhex")
{
    nos::stringstream writer;
    nos::current_ostream = &writer;
    nos::printhexln(0xABCD);
}