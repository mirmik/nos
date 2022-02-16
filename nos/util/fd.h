#ifndef NOS_UTIL_FD_H
#define NOS_UTIL_FD_H

#include <signal.h>
//#include <unistd.h>
//#include <fcntl.h>

namespace nos
{
	namespace osutil
	{
		static int nonblock(int, bool)
		{
                        /*if (fd < 0) return -1;
			int flags = fcntl(fd, F_GETFL, 0);
			if (flags < 0) return -1;
			flags = en ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
                        return fcntl(fd, F_SETFL, flags) == 0;*/
                    return 0;
		}

	}
}

#endif
