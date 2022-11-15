#include <chrono>
#include <doctest/doctest.h>
#include <fcntl.h>
#include <nos/input.h>
#include <nos/io/file.h>
#include <nos/print.h>
#include <thread>
#include <unistd.h>

using namespace std::chrono_literals;

TEST_CASE("nos::file::timeouted_read")
{
    int fds[2];
    pipe(fds);

    nos::file f(fds[0]);

    char buf[10];
    auto ans = f.timeouted_read(buf, 10, std::chrono::milliseconds(10));

    CHECK_EQ(ans, nos::input_error::timeout());
}

TEST_CASE("nos::file::timeouted_read")
{
    int fds[2];
    pipe(fds);

    nos::file f(fds[0]);
    nos::file i(fds[1]);

    i.write("hello", 5);

    std::this_thread::sleep_for(10ms);

    char buf[10];
    auto ans = f.timeouted_read(buf, 10, std::chrono::milliseconds(10));

    CHECK_EQ(*ans, 5);
    CHECK_EQ(std::string(buf, 5), "hello");
}

TEST_CASE("nos::timeouted_readline_from")
{
    int fds[2];
    pipe(fds);

    nos::file f(fds[0]);

    auto result =
        nos::timeouted_readline_from(f, std::chrono::milliseconds(10));

    CHECK_EQ(bool(result), false);
    CHECK_EQ(result.error().is_timeout(), true);
}

TEST_CASE("nos::timeouted_readline_from")
{
    int fds[2];
    pipe(fds);

    nos::file f(fds[0]);
    nos::file i(fds[1]);

    nos::println_to(i, "hello");
    nos::println_to(i, "world");

    auto result =
        nos::timeouted_readline_from(f, std::chrono::milliseconds(10));

    CHECK_EQ(*result, "hello");
}

/*
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

TEST_CASE("nos::timeouted_read_until_from")
{
    int fds[2];
    pipe(fds);

    nos::file f(fds[0]);
    nos::file i(fds[1]);

    nos::print_to(i, "hell");
    nos::print_to(i, "wrld");

    auto curtime = std::chrono::system_clock::now();
    auto [line, is_timeout] =
        nos::timeouted_read_until_from(std::chrono::milliseconds(10), f, "o");
    auto endtime = std::chrono::system_clock::now();

    CHECK_EQ(line, "hellwrld");
    CHECK_EQ(is_timeout, true);
    CHECK_GT(endtime - curtime, std::chrono::milliseconds(10));
}

TEST_CASE("nos::timeouted_read_until_from")
{
    int fds[2];
    pipe(fds);

    nos::file f(fds[0]);
    nos::file i(fds[1]);

    auto thr = std::thread([&]() {
        i.write("h", 1);
        std::this_thread::sleep_for(1ms);

        for (int j = 0; j < 100; ++j)
        {
            i.write("e", 1);
            std::this_thread::sleep_for(1ms);
        }

        i.write("l", 1);
        std::this_thread::sleep_for(1ms);

        i.write("l", 1);
        std::this_thread::sleep_for(1ms);

        i.write("o", 1);
        std::this_thread::sleep_for(1ms);

        i.write("l", 1);
        std::this_thread::sleep_for(1ms);

        i.write("l", 1);
        std::this_thread::sleep_for(1ms);
    });

    auto curtime = std::chrono::system_clock::now();
    auto [line, is_timeout] =
        nos::timeouted_read_until_from(std::chrono::milliseconds(200), f, "o");
    auto endtime = std::chrono::system_clock::now();

    thr.join();

    CHECK_EQ(line,
             std::string("h") + std::string(100, 'e') + std::string("llo"));
    CHECK_EQ(is_timeout, false);
    CHECK_GT(endtime - curtime, std::chrono::milliseconds(104));
    CHECK_LT(endtime - curtime, std::chrono::milliseconds(200));
}

TEST_CASE("onebyte read")
{
    int fds[2];
    pipe(fds);

    nos::file f(fds[0]);
    nos::file i(fds[1]);

    auto thr = std::thread([&]() {
        for (int j = 0; j < 20; ++j)
        {
            i.write("helloworld", 10);
            std::this_thread::sleep_for(1ms);
        }

        i.write(".", 1);
        std::this_thread::sleep_for(1ms);
    });

    auto [line, is_timeout] =
        nos::timeouted_read_until_from(std::chrono::milliseconds(200), f, ".");
    thr.join();

    std::string str;
    for (int j = 0; j < 20; ++j)
        str += "helloworld";
    str += ".";

    CHECK_EQ(line, str);
    CHECK_EQ(is_timeout, false);
}
*/