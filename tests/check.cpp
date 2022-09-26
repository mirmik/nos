#include <doctest/doctest.h>
#include <nos/check.h>

TEST_CASE("check")
{
    int i = 0;
    try
    {
        NOS_CHECK(false);
    }
    catch (const nos::check_error &e)
    {
        i++;
    }
    CHECK_EQ(i, 1);
}

TEST_CASE("check_eq")
{
    int i = 0;
    try
    {
        NOS_CHECK_EQ(0, 1);
    }
    catch (const nos::check_error &e)
    {
        i++;
    }
    CHECK_EQ(i, 1);
}