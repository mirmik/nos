#include <nos/log/logger.h>
#include <nos/log/target.h>

#include <string>

namespace nos
{
	namespace log
	{
		class tlogger : public nos::log::logger
		{
		private:
			std::vector<nos::log::target*> targets;

		public:
			std::string name;

			std::string pattern = "[{level}]{logger}: {msg}";
			level minlevel = level::trace;

		public:
			tlogger(const std::string& _name) : name(_name) {}

			void link(target* tgt)
			{
				targets.push_back(tgt);
			}

			void set_level(level lvl)
			{
				minlevel = lvl;
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

			void clear_targets() { targets.clear(); } 

			void set_pattern(const char* pattern) 
			{
				this->pattern = pattern;
			}

			void log(level lvl, const char* fmt, const visitable_arglist& arglist) override
			{
				log(lvl, nos::format(fmt, arglist));
			}
		};
	};
}