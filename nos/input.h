/** @file */

#ifndef NOS_INPUT_H
#define NOS_INPUT_H

#include <chrono>
#include <stdlib.h>
#include <string>

namespace nos
{
    class istream;
    extern istream *current_istream;

    std::string read_from(nos::istream &is, size_t sz);
    std::string readline_from(nos::istream &is);
    int read_until(nos::istream &is, char *buf, size_t buflen, char delim);
    int read_paired(nos::istream &is,
                    char *buf,
                    size_t buflen,
                    char a,
                    char b,
                    bool ignore = true);

    int read_with_timeout_ms(nos::istream &is,
                             char *buf,
                             size_t buflen,
                             int timeout_ms);
    std::string readall_from(nos::istream &is);
    std::string readline();

    std::pair<std::string, bool>
    timeouted_readline_from(std::chrono::nanoseconds ms, nos::istream &is);

    std::string read_until_from(nos::istream &is,
                                const std::string_view &delimiters);

    std::pair<std::string, bool>
    timeouted_read_until_from(std::chrono::nanoseconds ms,
                              nos::istream &is,
                              const std::string_view &delimiters);

    [[deprecated]] std::string readline(nos::istream &is);
}

#include <nos/io/istream.h>

#endif
