#ifndef NOS_LOG_TLOGGER_H
#define NOS_LOG_TLOGGER_H

#include <nos/log/logger.h>

#include <string>
#include <memory>

namespace nos
{
	namespace log
	{
		class target;

		class tlogger : public nos::log::logger
		{
		private:
			std::vector<nos::log::target*> targets;

		public:
			std::string name;

			std::string pattern = "[{level}]{logger}: {msg}";
			level minlevel = level::trace;

		public:
			tlogger(const std::string& _name);

			void link(target* tgt);

			void set_level(level lvl);

			/// Logging method implementation
			void log(level lvl, std::string&& msg);

			void clear_targets(); 

			void set_pattern(const char* pattern);

			void log(level lvl, const char* fmt, const visitable_arglist& arglist) override;
		};
	}
}

#endif