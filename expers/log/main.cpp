#include <nos/log.h>
#include <nos/log/targets/stdout.h>

int main ()
{
	nos::log::stdout_target stdout_target;

	stdout_target.set_format("{level:u}|{datetime}|{msg}");
	stdout_target.set_level(nos::log::debug);

	nos::log::logger syslogger("syslogger");

	syslogger.link(&stdout_target);


	syslogger.debug("HelloWorld");
}