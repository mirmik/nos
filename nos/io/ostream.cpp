#include <nos/io/ostream.h>
#include <nos/print/stdtype.h>

int nos::ostream::fill(char c, size_t len)
{
    size_t _len = len;
    while (_len--)
    {
        this->putbyte(c);
    }

    return len;
}

int nos::ostream::write_upper(const void *_ptr, size_t sz)
{
    char *ptr = (char *)_ptr;
    size_t _sz = sz;
    while (_sz--)
        putchar(toupper(*ptr++));
    return sz;
}

int nos::ostream::write_lower(const void *_ptr, size_t sz)
{
    char *ptr = (char *)_ptr;
    size_t _sz = sz;
    while (_sz--)
        putchar(tolower(*ptr++));
    return sz;
}
