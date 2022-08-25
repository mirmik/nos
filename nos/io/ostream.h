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

        int putbyte(char c)
        {
            return write(&c, 1);
        }

        int fill(char c, size_t len);

        virtual int flush()
        {
            return 0;
        }

        virtual ~ostream() = default;
    };
}

#endif
