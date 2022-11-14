/** @file */

#ifndef NOS_INPUT_H
#define NOS_INPUT_H

#include <chrono>
#include <nos/util/error.h>
#include <nos/util/expected.h>
#include <stdlib.h>
#include <string>
#include <string_view>

namespace nos
{
    struct read_error
    {
        bool _is_timeout = false;
        bool _is_closed = false;

        static read_error timeout()
        {
            return {true, false};
        }

        static read_error closed()
        {
            return {false, true};
        }

        static read_error ok()
        {
            return {false, false};
        }

        bool is_timeout() const
        {
            return _is_timeout;
        }

        bool is_closed() const
        {
            return _is_closed;
        }

        bool is_ok() const
        {
            return !(_is_timeout || _is_closed);
        }

        operator bool() const
        {
            return is_ok();
        }
    };

    class istream;
    extern istream *current_istream;

    nos::expected<std::string, nos::errstring> read_from(nos::istream &is,
                                                         size_t sz);

    // std::string readline_from(nos::istream &is);
    nos::expected<std::string, nos::errstring> readline_from(nos::istream &is);

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
    nos::expected<std::string, nos::errstring> readline();

    nos::expected<std::string, nos::errstring>
    read_until_from(nos::istream &is, const std::string_view &delimiters);

    /*std::pair<std::string, bool>
    timeouted_read_until_from(std::chrono::nanoseconds ms,
                              nos::istream &is,
                              const std::string_view &delimiters);*/

    nos::expected<std::string, read_error>
    timeouted_readline_from(nos::istream &is, std::chrono::nanoseconds ms);

}

#include <nos/io/istream.h>

#endif
