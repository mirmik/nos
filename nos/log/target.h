#ifndef NOS_LOG_TARGET_H
#define NOS_LOG_TARGET_H

#include <nos/log/logmsg.h>
#include <memory>

namespace nos
{
	namespace log
	{
		class target
		{
		protected:
			std::string fmt = "[{level}]{logger}: {msg}";
			nos::log::level lvl = {};

		public:
			virtual ~target() = default;
			virtual void log(std::shared_ptr<nos::log::logmsg> logmsg) = 0;

			void set_format(const nos::buffer & fmt);
			void set_level(nos::log::level lvl);
		};
	}
}

#endif
