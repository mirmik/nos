#ifndef NOS_LOG_LEVEL_H
#define NOS_LOG_LEVEL_H

#include <string_view>

namespace nos
{
	namespace log
	{
		enum level
		{
			trace,
			debug,
			info,
			warn,
			error,
			fault,
		};

		const char* level_to_string(level lvl);
		level level_from_string(const std::string_view & str);
	}
}

#endif
