#include <nos/log/targets/tcpspam.h>

#include <nos/log/tlogger.h>
#include <nos/fprint.h>

using namespace nos::argument_literal;

void nos::log::tcpspam_target::log(std::shared_ptr<nos::log::logmsg> lmsg)
{
	char buf[80];
	strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", &lmsg->timestamp);

	nos::fprintln(fmt.c_str(),
	              "level"_a = nos::log::level_to_string(lmsg->lvl),
	              "logger"_a = lmsg->logger->name,
	              "msg"_a = lmsg->text,
	              "datetime"_a = buf);
}
