#ifndef NOS_UTIL_FD_H
#define NOS_UTIL_FD_H

#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

namespace nos
{
	namespace osutil
	{
		int nonblock(int fd, bool en);
	}
}

#endif
