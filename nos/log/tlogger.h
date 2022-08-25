#ifndef NOS_LOG_TLOGGER_H
#define NOS_LOG_TLOGGER_H

#include <memory>
#include <nos/log/logger.h>
#include <string>

namespace nos
{
    namespace log
    {
        class target;

        class tlogger : public nos::log::logger
        {
        private:
            std::vector<nos::log::target *> targets = {};

        public:
            tlogger() = default;
            tlogger(const std::string &_name);

            void link(target *tgt);

            /// Logging method implementation
            void log(level lvl, std::string &&msg);

            void clear_targets();

            void log(level lvl,
                     const std::string_view &fmt,
                     const visitable_arglist &arglist) override;
        };
    }
}

#endif