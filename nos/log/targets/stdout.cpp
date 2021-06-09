#include <nos/log/targets/stdout.h>

#include <nos/log/target.h>
#include <nos/log/level.h>

#include <nos/print.h>
#include <nos/fprint.h>
#include <nos/print/stdtype.h>
#include <nos/fprint/stdtype.h>

#include <nos/log/tlogger.h>

using namespace nos::argument_literal;

void nos::log::stdout_target::log(std::shared_ptr<nos::log::logmsg> lmsg)
{
	char buf[80];
	strftime(buf, sizeof(buf), "%d-%m-%Y %H:%M:%S", &lmsg->timestamp);

	nos::fprintln(fmt.c_str(),
	              "level"_a = nos::log::level_to_string(lmsg->lvl),
	              "logger"_a = lmsg->logger->name,
	              "msg"_a = lmsg->text,
	              "datetime"_a = buf);
}