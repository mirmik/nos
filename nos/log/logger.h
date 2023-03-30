#ifndef NOS_LOGGER_H
#define NOS_LOGGER_H

#include <nos/fprint.h>
#include <nos/log/level.h>
#include <nos/print.h>
#include <string>
#include <string_view>

namespace nos
{
    namespace log
    {
        class logger
        {
        public:
            level _minlevel = level::Trace;
            std::string _name = "undefined";
            std::string _pattern =
                std::string("[{level}] {msg}") + newline_string;

        public:
            logger() = default;
            logger(const logger &) = default;
            logger(logger &&) = default;
            logger &operator=(const logger &) = default;
            logger &operator=(logger &&) = default;
            logger(const std::string &_name) : _name(_name) {}

            std::string name() const;

            std::string pattern() const;

            level minlevel() const;

            logger &set_name(const std::string &_name);

            logger &set_level(level lvl);

            logger &set_pattern(const std::string &pattern);

            virtual void log(level lvl,
                             const std::string_view &msgfmt,
                             const visitable_arglist &arglist);
            virtual ~logger() = default;

            template <typename... Args>
            inline void
            log(level lvl, const std::string_view &fmt, const Args &...args)
            {
                log(lvl,
                    fmt,
                    visitable_arglist(
                        {visitable_argument(args, nos::format_visitor())...}));
            }

            template <typename... Args> inline void trace(const Args &...args)
            {
                log(level::Trace, args...);
            }
            template <typename... Args> inline void debug(const Args &...args)
            {
                log(level::Debug, args...);
            }
            template <typename... Args> inline void info(const Args &...args)
            {
                log(level::Info, args...);
            }
            template <typename... Args> inline void warn(const Args &...args)
            {
                log(level::Warn, args...);
            }
            template <typename... Args> inline void error(const Args &...args)
            {
                log(level::Error, args...);
            }
            template <typename... Args> inline void fault(const Args &...args)
            {
                log(level::Fault, args...);
            }
        };

        void set_default_logger(logger *logger);
        logger *default_logger();

        template <typename... Args>
        inline void
        log(level lvl, const std::string_view &fmt, const Args &...args)
        {
            if (default_logger())
                default_logger()->log(lvl,
                                      fmt,
                                      visitable_arglist({visitable_argument(
                                          args, nos::format_visitor())...}));
        }

        template <typename... Args> inline void trace(const Args &...args)
        {
            log(level::Trace, args...);
        }
        template <typename... Args> inline void debug(const Args &...args)
        {
            log(level::Debug, args...);
        }
        template <typename... Args> inline void info(const Args &...args)
        {
            log(level::Info, args...);
        }
        template <typename... Args> inline void warn(const Args &...args)
        {
            log(level::Warn, args...);
        }
        template <typename... Args> inline void error(const Args &...args)
        {
            log(level::Error, args...);
        }
        template <typename... Args> inline void fault(const Args &...args)
        {
            log(level::Fault, args...);
        }
    }
}

#endif
