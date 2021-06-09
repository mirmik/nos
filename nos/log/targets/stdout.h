#ifndef NOS_LOG_TARGETS_STDOUT_H
#define NOS_LOG_TARGETS_STDOUT_H

#include <memory>

#include <nos/log/logmsg.h>
#include <nos/log/target.h>

namespace nos 
{
	namespace log 
	{
		class stdout_target : public nos::log::target 
		{
			void log(std::shared_ptr<nos::log::logmsg> lmsg) override;
		};
	}
}

#endif
