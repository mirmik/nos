#ifndef NOS_IO_ISTREAM_H
#define NOS_IO_ISTREAM_H

#include <chrono>
#include <nos/input/input_error.h>
#include <nos/util/expected.h>
#include <stdlib.h>
#include <string>

using namespace std::chrono_literals;

namespace nos
{
    class istream
    {
        std::chrono::nanoseconds _input_timeout = 0ns;

    public:
        virtual ~istream() = default;
        virtual nos::expected<int, nos::input_error> read(void *ptr,
                                                          size_t sz) = 0;

        void set_input_timeout(std::chrono::nanoseconds timeout)
        {
            this->_input_timeout = timeout;
        }

        std::chrono::nanoseconds input_timeout() const
        {
            return this->_input_timeout;
        }

        int ignore()
        {
            char c;
            int readed = read(&c, 1);
            return readed;
        }
        int ignore(int i)
        {
            int j = i;
            while (j--)
                ignore();
            return i;
        }
    };
}

#endif
