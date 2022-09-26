#ifndef NOS_CHECK_H
#define NOS_CHECK_H

#include <exception>
#include <nos/fprint.h>
#include <nos/util/location.h>
#include <nos/util/macro.h>
#include <string>

namespace nos
{
    class check_error : public std::exception
    {
        std::string _msg;

    public:
        check_error(const std::string &msg) : _msg(msg) {}

        const char *what() const noexcept override
        {
            return _msg.c_str();
        }
    };
}

#define NOS_CHECK(...)                                                         \
    if (!(__VA_ARGS__))                                                        \
    {                                                                          \
        NOS_CURRENT_LOCATION(loc);                                             \
        std::string str = nos::format("Error checked in location \n"           \
                                      "\tline:{}\n"                            \
                                      "\tfile:{}\n"                            \
                                      "\tfunc:{}\n"                            \
                                      "\tcond:{}\n\f",                         \
                                      loc.line,                                \
                                      loc.file,                                \
                                      loc.func,                                \
                                      NOS_STRINGIFY(__VA_ARGS__));             \
        throw nos::check_error(str);                                           \
    }

#endif