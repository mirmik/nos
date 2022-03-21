#ifndef NOS_LOGGER_H
#define NOS_LOGGER_H

#include <nos/print.h>
#include <nos/fprint.h>
#include <nos/log/level.h>

#define WITHOUT_LOG 1

namespace nos
{
	namespace log
	{
		class logger 
		{
		public:
			virtual void log(level lvl, const char* fmt, const visitable_arglist& arglist) = 0;
			virtual ~logger() = default;

			template <typename ... Args>
			inline void log(level lvl, const char* fmt, const Args& ... args)
			{
				log(lvl, fmt, visitable_arglist ({ visitable_argument(args, nos::format_visitor()) ... }));
			}

			template <typename ... Args> inline void trace(const Args& ... args) { log(level::trace, args ...); }
			template <typename ... Args> inline void debug(const Args& ... args) { log(level::debug, args ...); }
			template <typename ... Args> inline void info(const Args& ... args) { log(level::info, args ...); }
			template <typename ... Args> inline void warn(const Args& ... args) { log(level::warn, args ...); }
			template <typename ... Args> inline void error(const Args& ... args) { log(level::error, args ...); }
			template <typename ... Args> inline void fault(const Args& ... args) { log(level::fault, args ...); }
		};
	}
}

#endif
