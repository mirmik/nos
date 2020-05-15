#ifndef NOS_LOG_LEVEL_H
#define NOS_LOG_LEVEL_H

#include <igris/buffer.h>
#include <igris/util/bug.h>

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
		level level_from_string(const igris::buffer str);
	}
}

#endif