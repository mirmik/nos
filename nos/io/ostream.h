#ifndef NOS_IO_OSTREAM_H
#define NOS_IO_OSTREAM_H

#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static inline char __nos_half2hex(uint8_t n)
{
    return (char)(n < 10 ? '0' + n : 'A' - 10 + n);
}

namespace nos
{
    class ostream
    {
    public:
        virtual int write(const void *ptr, size_t sz) = 0;
        int write_upper(const void *ptr, size_t sz);
        int write_lower(const void *ptr, size_t sz);

        int put(uint8_t byte)
        {
            return write(&byte, 1);
        }

        template <typename... Args> int print(const Args &... args);

        template <typename Arg> ostream &operator<<(const Arg &arg)
        {
            print(arg);
            return *this;
        }

        template <typename... Args> int println(const Args &... args);

        int println()
        {
            return write("\r\n", 2);
        }

        int putbyte(char c)
        {
            return write(&c, 1);
        }

        int printhex(char c)
        {
            char buf[2];
            buf[0] = __nos_half2hex((uint8_t)((c & 0xF0) >> 4));
            buf[1] = __nos_half2hex((uint8_t)(c & 0x0F));
            return write(buf, 2);
        }

        int printhex(void *ptr, size_t sz)
        {
            size_t ret = 0;
            char *_ptr = (char *)ptr;

            for (unsigned int i = 0; i < sz; ++i)
            {
                ret += printhex(*_ptr++);
            }

            return ret;
        }

        template <typename O> int printhex(const O &o)
        {
            return printhex((void *)&o, sizeof(O));
        }

        int fill(char c, size_t len);
        int printptr(const void *ptr);

        virtual int flush()
        {
            return 0;
        }
        virtual ~ostream() = default;
    };
}

#endif
