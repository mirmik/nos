#ifndef NOS_LOGGER_H
#define NOS_LOGGER_H

#include <nos/fprint.h>
#include <nos/log/level.h>
#include <nos/print.h>
#include <string>
#include <string_view>

#define WITHOUT_LOG 1

namespace nos
{
    namespace log
    {
        class logger
        {
            std::string pattern = "[{level}] {msg}\n";
            std::string _name = "";
            level minlevel = level::Trace;

        public:
            logger() = default;
            logger(const std::string &_name) : _name(_name) {}

            std::string name() const
            {
                return _name;
            }

            void set_level(level lvl)
            {
                minlevel = lvl;
            }

            void set_pattern(const std::string_view &pattern)
            {
                this->pattern = pattern;
            }

            virtual void log(level lvl,
                             const std::string_view &msgfmt,
                             const visitable_arglist &arglist)
            {
                using namespace nos::argument_literal;
                auto msg = nos::format(msgfmt, arglist);
                nos::fprint(pattern,
                            "level"_a = nos::log::level_to_string(lvl),
                            "logger"_a = _name,
                            "msg"_a = msg);
            };
            virtual ~logger() = default;

            template <typename... Args>
            inline void
            log(level lvl, const std::string_view &fmt, const Args &... args)
            {
                log(lvl,
                    fmt,
                    visitable_arglist(
                        {visitable_argument(args, nos::format_visitor())...}));
            }

            template <typename... Args> inline void trace(const Args &... args)
            {
                log(level::Trace, args...);
            }
            template <typename... Args> inline void debug(const Args &... args)
            {
                log(level::Debug, args...);
            }
            template <typename... Args> inline void info(const Args &... args)
            {
                log(level::Info, args...);
            }
            template <typename... Args> inline void warn(const Args &... args)
            {
                log(level::Warn, args...);
            }
            template <typename... Args> inline void error(const Args &... args)
            {
                log(level::Error, args...);
            }
            template <typename... Args> inline void fault(const Args &... args)
            {
                log(level::Fault, args...);
            }
        };

        extern logger stdlogger;
        template <typename... Args>
        inline void
        log(level lvl, const std::string_view &fmt, const Args &... args)
        {
            stdlogger.log(lvl,
                          fmt,
                          visitable_arglist({visitable_argument(
                              args, nos::format_visitor())...}));
        }

        template <typename... Args> inline void trace(const Args &... args)
        {
            log(level::Trace, args...);
        }
        template <typename... Args> inline void debug(const Args &... args)
        {
            log(level::Debug, args...);
        }
        template <typename... Args> inline void info(const Args &... args)
        {
            log(level::Info, args...);
        }
        template <typename... Args> inline void warn(const Args &... args)
        {
            log(level::Warn, args...);
        }
        template <typename... Args> inline void error(const Args &... args)
        {
            log(level::Error, args...);
        }
        template <typename... Args> inline void fault(const Args &... args)
        {
            log(level::Fault, args...);
        }

    }
}

#endif
