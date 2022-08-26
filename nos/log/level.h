#ifndef NOS_LOG_LEVEL_H
#define NOS_LOG_LEVEL_H

#include <nos/util/buffer.h>

namespace nos
{
    namespace log
    {
        enum class level
        {
            Trace,
            Debug,
            Info,
            Warn,
            Error,
            Fault,
        };

        const char *level_to_string(level lvl);
        level level_from_string(const nos::buffer &str);
    }
}

#endif
