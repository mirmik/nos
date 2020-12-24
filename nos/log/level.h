#ifndef NOS_LOG_LEVEL_H
#define NOS_LOG_LEVEL_H

#include <nos/util/buffer.h>

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
		level level_from_string(const nos::buffer str);
	}
}

#endif
