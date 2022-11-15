/** @file */

#ifndef NOS_INPUT_H
#define NOS_INPUT_H

#include <chrono>
#include <nos/input/input_error.h>
#include <nos/util/error.h>
#include <nos/util/expected.h>
#include <stdlib.h>
#include <string>
#include <string_view>

namespace nos
{
    class istream;
    extern istream *current_istream;

    nos::expected<std::string, nos::input_error> read_from(nos::istream &is,
                                                           size_t sz);

    nos::expected<std::string, nos::input_error>
    readline_from(nos::istream &is);

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
    nos::expected<std::string, nos::input_error> readline();

    nos::expected<std::string, nos::input_error>
    read_until_from(nos::istream &is, const std::string_view &delimiters);

    /*std::pair<std::string, bool>
    timeouted_read_until_from(std::chrono::nanoseconds ms,
                              nos::istream &is,
                              const std::string_view &delimiters);*/

    nos::expected<std::string, nos::input_error>
    timeouted_readline_from(nos::istream &is, std::chrono::nanoseconds ms);

}

#include <nos/io/istream.h>

#endif
