#ifndef NOS_IO_ISTREAM_H
#define NOS_IO_ISTREAM_H

#include <chrono>
#include <nos/input.h>
#include <stdexcept>
#include <stdlib.h>
#include <string>

namespace nos
{
    class istream
    {
    public:
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

        std::string read(size_t size)
        {
            std::string ret;
            ret.resize(size);
            size_t readlen = read(&ret[0], size);
            ret.resize(readlen);
            return ret;
        }

        virtual int read(void *ptr, size_t sz) = 0;
        virtual ~istream() = default;

        // @return1 - количество прочитанных байт
        // @return2 - случился ли таймаут
        /*virtual std::pair<int, bool>
        timeouted_read(void *ptr, size_t sz, std::chrono::nanoseconds ms)
        {
            (void)ptr;
            (void)sz;
            (void)ms;
            // throw std::runtime_error("not implemented");
        }*/
    };
}

#endif
