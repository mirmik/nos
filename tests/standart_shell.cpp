/*#include <doctest/doctest.h>
#include <nos/io/sstream.h>
#include <nos/shell/standart.h>

#include <thread>

using namespace std::chrono_literals;

nos::cancel_token_source cancel_source;
TEST_CASE("standart shell")
{
    nos::executor exec;
    exec.add_command(nos::command(
        "hello", "", +[](const nos::argv &, nos::ostream &os) -> int {
            os.write("helloworld", 10);
            cancel_source.cancel();
            return 0;
        }));

    nos::stringstream is("hello\r\n");
    nos::stringstream os;
    std::thread thr(nos::shell_io_thread_function,
                    std::ref(is),
                    std::ref(os),
                    std::ref(exec),
                    cancel_source.token());
    thr.join();

    CHECK_EQ(os.str(), "$ helloworld");
}*/