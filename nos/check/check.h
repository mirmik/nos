#ifndef NOS_CHECK_H
#define NOS_CHECK_H

#include <exception>
#include <nos/check/env.h>
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

std::string nos_location_part(struct nos_location loc)
{
    return nos::format("Error checked in location \n"
                       "\tline:{}\n"
                       "\tfile:{}\n"
                       "\tfunc:{}\n",
                       loc.line,
                       loc.file,
                       loc.func);
}

#define NOS_CHECK(...)                                                         \
    if (!(__VA_ARGS__))                                                        \
    {                                                                          \
        NOS_CURRENT_LOCATION(loc);                                             \
        std::string str = nos::format("{}"                                     \
                                      "\tcond:{}\n\f",                         \
                                      nos_location_part(loc),                  \
                                      NOS_STRINGIFY(__VA_ARGS__));             \
        NOS_CHECK_ENV_RAISE(str);                                              \
    }

#define NOS_CHECK_EQ(a, b)                                                     \
    if (a != b)                                                                \
    {                                                                          \
        NOS_CURRENT_LOCATION(loc);                                             \
        std::string str =                                                      \
            nos::format("{}"                                                   \
                        "\tcond:{}\n"                                          \
                        "\tleft: {}\n"                                         \
                        "\tright: {}\n",                                       \
                        nos_location_part(loc),                                \
                        NOS_STRINGIFY(a) " == " NOS_STRINGIFY(b),              \
                        a,                                                     \
                        b);                                                    \
        NOS_CHECK_ENV_RAISE(str);                                              \
    }

#define NOS_CHECK_LT(a, b)                                                     \
    if (a >= b)                                                                \
    {                                                                          \
        NOS_CURRENT_LOCATION(loc);                                             \
        std::string str = nos::format("{}"                                     \
                                      "\tcond:{}\n"                            \
                                      "\tleft: {}\n"                           \
                                      "\tright: {}\n",                         \
                                      nos_location_part(loc),                  \
                                      NOS_STRINGIFY(a) " < " NOS_STRINGIFY(b), \
                                      a,                                       \
                                      b);                                      \
        NOS_CHECK_ENV_RAISE(str);                                              \
    }

#define NOS_CHECK_GT(a, b)                                                     \
    if (a <= b)                                                                \
    {                                                                          \
        NOS_CURRENT_LOCATION(loc);                                             \
        std::string str = nos::format("{}"                                     \
                                      "\tcond:{}\n"                            \
                                      "\tleft: {}\n"                           \
                                      "\tright: {}\n",                         \
                                      nos_location_part(loc),                  \
                                      NOS_STRINGIFY(a) " > " NOS_STRINGIFY(b), \
                                      a,                                       \
                                      b);                                      \
        NOS_CHECK_ENV_RAISE(str);                                              \
    }

#endif