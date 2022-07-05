#ifndef NOS_UTIL_STRING_H
#define NOS_UTIL_STRING_H

#include <vector>
#include <string>
#include <nos/util/buffer.h>

namespace nos 
{
    std::string replace(const std::string &src, const std::string &oldsub,
                        const std::string &newsub);

    std::vector<std::string> split(const nos::buffer &str, char delim = ' ');
    std::vector<std::string> split(const nos::buffer &str,
                                   const char *delims);

    std::string join(const std::vector<std::string> &, char delim);

    template <class Iter>
    std::string join(Iter start, Iter end, const char *delim,
                     const char *prefix, const char *postfix);

    std::string trim(const nos::buffer &view);
}

#endif