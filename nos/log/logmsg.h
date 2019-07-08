#ifndef NOS_LOG_LOGMSG_H
#define NOS_LOG_LOGMSG_H

#include <ctime>
#include <cstdio>

#include <nos/log/level.h>

namespace nos
{
	namespace log
	{
		class logger;

		class logmsg
		{
		public:
			nos::log::logger * logger; 
			level lvl;
			std::string text;
			std::tm timestamp;

		public:
			logmsg(
				nos::log::logger * logger,
				nos::log::level lvl, 
				std::string && str, 
				std::tm & timestamp
			) :
				logger(logger),
				lvl(lvl),
				text(std::move(str)),
				timestamp(timestamp)
			{}
		};
	}
}

#endif