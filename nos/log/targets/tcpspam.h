/*ifndef NOS_LOG_TARGETS_TCPSPAM_H
#define NOS_LOG_TARGETS_TCPSPAM_H

#include <nos/log/logmsg.h>
#include <nos/log/target.h>
#include <memory>

namespace nos
{
	namespace log
	{
		class tcpspam_target : public nos::log::target
		{
			int port;
		public:
			tcpspam_target(int port) : port(port) {}

			void log(std::shared_ptr<nos::log::logmsg> lmsg) override;
		};
	}
}

#endif
/