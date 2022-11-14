#include <nos/input.h>
#include <nos/io/file.h>

int nos::read_with_timeout_ms(nos::istream &is,
                              char *buf,
                              size_t buflen,
                              int timeout_ms)
{
    (void)is;
    (void)buf;
    (void)buflen;
    (void)timeout_ms;
    return 0;
}
