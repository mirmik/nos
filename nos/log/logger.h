#ifndef NOS_LOGGER_H
#define NOS_LOGGER_H

#include <nos/print.h>
#include <nos/fprint.h>
#include <nos/log/level.h>
#include <nos/log/target.h>

#include <vector>
#include <memory>

#define WITHOUT_LOG 1

namespace nos
{
	namespace log
	{
		class logger
		{
		private:
			std::vector<nos::log::target*> targets;

		public:
			std::string name;

		public:
			logger(const std::string& _name) : name(_name) {}

			void link(target* tgt)
			{
				targets.push_back(tgt);
			}

			/// Logging method implementation
			void log(level lvl, std::string&& msg)
			{
				time_t current_time;
				struct tm  local_time;

				::time(&current_time);
				::localtime_r(&current_time, &local_time);

				std::shared_ptr<nos::log::logmsg> logmsg
				    = std::make_shared<nos::log::logmsg>
				      (
				          this,
				          lvl,
				          std::move(msg),
				          local_time
				      );

				for (auto * tgt : targets)
				{
					tgt->log(logmsg);
				}
			}

			void clear_targets();

//#if NOS_WITHOUT_LOG != 1
			template <typename ... Args>
			inline void log(level lvl, igris::buffer fmt, const Args& ... args)
			{
				log(lvl, nos::format(fmt, args ...));
			}

			template <typename ... Args> inline void trace(const Args& ... args) { log(level::trace, args ...); }
			template <typename ... Args> inline void debug(const Args& ... args) { log(level::debug, args ...); }
			template <typename ... Args> inline void info(const Args& ... args) { log(level::info, args ...); }
			template <typename ... Args> inline void warn(const Args& ... args) { log(level::warn, args ...); }
			template <typename ... Args> inline void error(const Args& ... args) { log(level::error, args ...); }
			template <typename ... Args> inline void fault(const Args& ... args) { log(level::fault, args ...); }

			/*#else

					template <typename ... Args>
					inline void log(level lvl, const char* fmt, Args&& ... args) {}

					template <typename ... Args>
					inline void log(level lvl, std::string& fmt, Args&& ... args) {}

					template <typename ... Args> inline void trace(Args&& ... args) {}
					template <typename ... Args> inline void debug(Args&& ... args) {}
					template <typename ... Args> inline void info(Args&& ... args) {}
					template <typename ... Args> inline void warn(Args&& ... args) {}
					template <typename ... Args> inline void error(Args&& ... args) {}
					template <typename ... Args> inline void fault(Args&& ... args) {}

			#endif*/
		};
	};
}

#endif
