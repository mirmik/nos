#include <chrono>
#include <doctest/doctest.h>
#include <fcntl.h>
#include <nos/input.h>
#include <nos/io/file.h>
#include <nos/print.h>
#include <thread>
#include <unistd.h>

using namespace std::chrono_literals;

//#warning TODO: timeouted_read
/*TEST_CASE("nos::file::timeouted_read")
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
}*/