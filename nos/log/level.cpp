#include <nos/log/level.h>

const char* nos::log::level_to_string(level lvl)
{
	switch (lvl)
	{
		case level::trace: return "trace";
		case level::debug: return "debug";
		case level::info : return " info";
		case level::warn : return " warn";
		case level::error: return "error";
		case level::fault: return "fault";
	}
	return nullptr;
}

nos::log::level nos::log::level_from_string(const nos::buffer & str)
{
	if      (str == "fault") return level::fault;
	else if (str == "error") return level::error;
	else if (str == "warn")  return level::warn;
	else if (str == "info")  return level::info;
	else if (str == "debug") return level::debug;
	else if (str == "trace") return level::trace;

	return level::trace;
}
