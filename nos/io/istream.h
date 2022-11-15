#ifndef NOS_IO_ISTREAM_H
#define NOS_IO_ISTREAM_H

#include <chrono>
#include <nos/input.h>
#include <nos/input/input_error.h>
#include <stdexcept>
#include <stdlib.h>
#include <string>

using namespace std::chrono_literals;

namespace nos
{
    class istream
    {
        std::chrono::nanoseconds _input_timeout = 0ns;

    public:
        void set_input_timeout(std::chrono::nanoseconds timeout)
        {
            this->_input_timeout = timeout;
        }

        std::chrono::nanoseconds input_timeout() const
        {
            return this->_input_timeout;
        }

        std::string readall()
        {
            std::string ret;

            int len;
            char buf[1024];

            while ((len = read(buf, 1024)) != 0)
            {
                ret.append(buf, len);
            }

            return ret;
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

        int read_until(char *buf, size_t buflen, char delim)
        {
            return nos::read_until(*this, buf, buflen, delim);
        }

        int read_paired(
            char *buf, size_t buflen, char a, char b, bool ignore = true)
        {
            return nos::read_paired(*this, buf, buflen, a, b, ignore);
        }

        nos::expected<std::string, nos::input_error> read(size_t size)
        {
            std::string ret;
            ret.resize(size);
            auto result = read(&ret[0], size);
            if (result)
            {
                ret.resize(*result);
                return ret;
            }
            else
            {
                return result.error();
            }
        }

        virtual nos::expected<int, nos::input_error> read(void *ptr,
                                                          size_t sz) = 0;

        virtual ~istream() = default;

        // @return1 - количество прочитанных байт
        // @return2 - случился ли таймаут
        virtual nos::expected<int, nos::input_error>
        timeouted_read(void *ptr, size_t sz, std::chrono::nanoseconds ms)
        {
            set_input_timeout(ms);
            return read(ptr, sz);
        }
    };
}

#endif
