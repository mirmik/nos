#include <chrono>
#include <doctest/doctest.h>
#include <fcntl.h>
#include <nos/input.h>
#include <nos/io/file.h>
#include <nos/print.h>
#include <unistd.h>

TEST_CASE("nos::file::timeouted_read")
{
    int fds[2];
    pipe(fds);

    nos::file f(fds[0]);

    char buf[10];
    auto [sts, is_timeout] =
        f.timeouted_read(buf, 10, std::chrono::milliseconds(10));

    CHECK_EQ(sts, 0);
    CHECK_EQ(is_timeout, true);
}

TEST_CASE("nos::file::timeouted_read")
{
    int fds[2];
    pipe(fds);

    nos::file f(fds[0]);
    nos::file i(fds[1]);

    i.write("hello", 5);

    char buf[10];
    auto [sts, is_timeout] =
        f.timeouted_read(buf, 10, std::chrono::milliseconds(10));

    CHECK_EQ(sts, 5);
    CHECK_EQ(is_timeout, false);
}

TEST_CASE("nos::timeouted_readline_from")
{
    int fds[2];
    pipe(fds);

    nos::file f(fds[0]);

    auto [line, is_timeout] =
        nos::timeouted_readline_from(std::chrono::milliseconds(10), f);

    CHECK_EQ(line, std::string());
    CHECK_EQ(is_timeout, true);
}

TEST_CASE("nos::timeouted_readline_from")
{
    int fds[2];
    pipe(fds);

    nos::file f(fds[0]);
    nos::file i(fds[1]);

    nos::println_to(i, "hello");
    nos::println_to(i, "world");

    auto [line, is_timeout] =
        nos::timeouted_readline_from(std::chrono::milliseconds(10), f);

    CHECK_EQ(line, "hello");
    CHECK_EQ(is_timeout, false);
}

TEST_CASE("nos::timeouted_read_until_from")
{
    int fds[2];
    pipe(fds);

    nos::file f(fds[0]);
    nos::file i(fds[1]);

    nos::println_to(i, "hello");
    nos::println_to(i, "world");

    auto [line, is_timeout] =
        nos::timeouted_read_until_from(std::chrono::milliseconds(10), f, "o");

    CHECK_EQ(line, "hello");
    CHECK_EQ(is_timeout, false);
}