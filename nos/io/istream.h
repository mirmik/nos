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
    public:
        virtual ~istream() = default;
        virtual nos::expected<int, nos::input_error> read(void *ptr,
                                                          size_t sz) = 0;

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
