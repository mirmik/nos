#ifndef NOS_LOG_TARGETS_TCPSPAM_H
#define NOS_LOG_TARGETS_TCPSPAM_H

#include <nos/log/target.h>
#include <nos/inet/tcpspam_server.h>
#include <nos/log/level.h>

#include <nos/print.h>
#include <nos/fprint.h>
#include <nos/print/stdtype.h>
#include <nos/fprint/stdtype.h>

using namespace nos::argument_literal;

namespace nos 
{
	namespace log 
	{
		class tcpspam_target : public nos::log::target 
		{
			int port;
public:
			tcpspam_target(int port) : port(port) {}


			//TODO
			void log(std::shared_ptr<nos::log::logmsg> lmsg) override
			{
				char buf[80];
				strftime(buf,sizeof(buf),"%d-%m-%Y %H:%M:%S",&lmsg->timestamp);

				nos::fprintln(fmt.c_str(), 
					"level"_a=nos::log::level_to_string(lmsg->lvl),
					"logger"_a=lmsg->logger->name,
					"msg"_a=lmsg->text,
					"datetime"_a=buf);
			}
		};
	}
}

#endif
