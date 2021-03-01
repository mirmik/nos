#ifndef NOS_LOG_TARGETS_BUFFER_TARGET_H
#define NOS_LOG_TARGETS_BUFFER_TARGET_H

#include <nos/log/target.h>


namespace nos
{
	namespace log
	{
		class buffer_target : public nos::log::target
		{
			char * buffer;
			char * ptr;

		public:
			buffer_target(int port) : port(port) {}


			//TODO
			void log(std::shared_ptr<nos::log::logmsg> lmsg) override
			{
			}
		};
	}
}

#endif